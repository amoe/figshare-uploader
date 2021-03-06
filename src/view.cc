#include <QObject>
#include <QDebug>
#include <QPlainTextEdit>
#include <QStandardPaths>
#include <QFileDialog>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QMenuBar>
#include <QIcon>
#include <QSize>
#include <QStringListModel>
#include <QTableView>

#include "optional.hpp"

#include "view.hh"
#include "presenter.hh"
#include "slot_adapter.hh"
#include "settings_dialog.hh"
#include "about_dialog.hh"
#include "field_encoder_model.hh"
#include "domain_dto.hh"
#include "field_mapping_table_model.hh"
#include "logging.hh"
#include "qt_utility.hh"
#include "options_editor_model.hh"
#include "options_editor_view.hh"

using nonstd::optional;
using nonstd::nullopt;

ViewImpl::ViewImpl(Presenter* presenter) : QMainWindow(), presenter(presenter) {
    QWidget* contentWidget = new QWidget(this);
    setWindowTitle("Figshare Uploader");

    QMenu* optionsMenu = new QMenu("Options");
    QAction* showSettingsAction = new QAction("Settings", this);
    optionsMenu->addAction(showSettingsAction);

    QMenu* helpMenu = new QMenu("Help");
    QAction* aboutAction = new QAction("About", this);
    helpMenu->addAction(aboutAction);

    // menuBar is a QMainWindow method.
    menuBar()->addMenu(optionsMenu);
    menuBar()->addMenu(helpMenu);
	
    // layout MUST be allocated on the heap here, if it goes out of scope, it
    // will simply stop layout out the widgets properly!
    // But, I think that we don't need to clean it up because the QWidget
    // destructor will delete it at the appropriate time.	
    QGridLayout* layout = new QGridLayout(contentWidget);

    QLabel* tokenLabel =  new QLabel("Token:");
    this->token = new QLineEdit(this);
    layout->addWidget(tokenLabel, 0, 0, 1, 1);
    layout->addWidget(this->token, 0, 1, 1, 11);

    QLabel* fileLabel =  new QLabel("File:");
    this->selectedFile = new QLineEdit(this);
    QPushButton* pickButton = new QPushButton("Pick", this);
    layout->addWidget(fileLabel, 1, 0, 1, 1);
    layout->addWidget(this->selectedFile, 1, 1, 1, 10);
    layout->addWidget(pickButton, 1, 11, 1, 1);

    this->actionButton = new QPushButton("Start upload process", this);
    layout->addWidget(this->actionButton, 2, 0, 1, 12);

    this->logger = new QPlainTextEdit("Waiting for file selection.");
    logger->setReadOnly(true);
    logger->setCenterOnScroll(true);
    layout->addWidget(logger, 3, 0, 1, 12);

    contentWidget->setLayout(layout);
    setCentralWidget(contentWidget);

    SlotAdapter slotAdapter(presenter, &Presenter::startUpload);
    connect(
        this->actionButton,
        &QPushButton::released,
        slotAdapter
    );

    SlotAdapter pickAdapter(presenter, &Presenter::pickFile);
    connect(
        pickButton,
        &QPushButton::released,
        pickAdapter
    );

    SlotAdapter aboutAdapter(presenter, &Presenter::showAboutDialog);

    connect(
        aboutAction,
        &QAction::triggered,
        aboutAdapter
    );

    SlotAdapter showSettingsDialogAdapter(presenter, &Presenter::showSettingsDialog);
    connect(showSettingsAction, &QAction::triggered, showSettingsDialogAdapter);
}

std::string ViewImpl::getSelectedFile() {
    QString content = selectedFile->text();
    QString native = QDir::toNativeSeparators(content);
    return native.toStdString();
}

std::string ViewImpl::getToken() {
    QString content = token->text();
    return content.toStdString();
}

void ViewImpl::setToken(string newToken) {
    token->setText(QString::fromStdString(newToken));
}


void ViewImpl::reportError(std::string errorText) {
    addLog("Error: " + errorText);
    QMessageBox::critical(this, "Error", QString::fromStdString(errorText));
}

// Overloaded version delegate to private Qt-signatured version
void ViewImpl::addLog(std::string logText) {
    addQLog(QString::fromStdString(logText));
}


void ViewImpl::addQLog(QString logText) {
    logger->appendPlainText(logText);
}

bool ViewImpl::showFileDialog() {
    QString documentsPath = 
        QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();
    QString fileName = QFileDialog::getOpenFileName(
        this, "Open File", documentsPath, "Excel documents (*.xlsx)"
    );

    if (fileName.isNull())
        return false;

    // We immediately need to delegate back to the presenter, which will call
    // us back later (on changeSourceFile) after storing the chosen filename.
    presenter->fileConfirmed(fileName.toStdString());
    
    return true;
}

// Wiring method for updating the view of the source file name.
void ViewImpl::setSourceFile(std::string sourceFile) {
    selectedFile->setText(QString::fromStdString(sourceFile));
}

void ViewImpl::setProgressReporter(ViewProgressAdapter* reporter) {
    this->reporter = reporter;

    connect(reporter, &ViewProgressAdapter::progressReport, this, &ViewImpl::addQLog);
}

void ViewImpl::showAboutDialog() {
    AboutDialog* aboutDialog = new AboutDialog(this);
    aboutDialog->exec();
}

void ViewImpl::showSettingsDialog(
    vector<string> headerFields, const MappingScheme& fieldMappings,
    const ConverterRegistry& converterRegistry

) {
    fieldMappingModel = new FieldMappingTableModel(
        headerFields, fieldMappings, this
    );
    converterListModel = new ConverterListModel(converterRegistry, this);

    connect(
        fieldMappingModel, &FieldMappingTableModel::mappingEncoderSet,
        this, &ViewImpl::onMappingEncoderSetOperation
    );

    SettingsDialog* settingsDialog = new SettingsDialog(
        fieldMappingModel, fieldEncoderModel, converterListModel, this
    );

    // We should be setting up the connections here.
    // We should connect to presenter.

    SlotAdapter slotAdapter(presenter, &Presenter::settingsConfirmed);
    connect(settingsDialog, &QDialog::accepted, slotAdapter);

    connect(
        settingsDialog, &SettingsDialog::fieldEncoderDialogConfirmed,
        this, &ViewImpl::onFieldEncoderConfigurationDialogConfirmed
    );

    connect(
        settingsDialog, &SettingsDialog::saveFieldMappingsRequested,
        this, &ViewImpl::onSaveFieldMappingsRequested
    );

    connect(
        settingsDialog, &SettingsDialog::loadFieldMappingsRequested,
        this, &ViewImpl::onLoadFieldMappingsRequested
    );

    // Block execution until "accepted" signal is emitted.
    settingsDialog->show();
}

void ViewImpl::setAvailableEncoders(vector<FieldEncoder>& availableEncoders) {
    fieldEncoderModel = new FieldEncoderModel(availableEncoders);
}

void ViewImpl::onFieldEncoderConfigurationDialogConfirmed(qt_dto::FieldEncoderConfigurationOperation dto) {
    spdlog::info("SIGNAL REACHED THE VIEWIMPL");
    domain::FieldEncoderListOperation result;

    result.index = dto.index.row();
    result.isTargetFieldSet = dto.targetFieldControlsChecked;
    result.targetFieldTypeId = dto.targetFieldTypeId;
    result.fieldName = dto.fieldName.toStdString();
    result.converterIndex = dto.selectedConverter.row();
    
    spdlog::info("Converter index was {}", result.converterIndex);
    
    result.newOptions = dto.optionsMap;

    // Map QList destructively
    vector<int> validationRuleIndices;
    auto& dtoRules = dto.selectedValidationRules;

    while (!dtoRules.isEmpty()) {
        QModelIndex index = dtoRules.takeFirst();
        validationRuleIndices.push_back(index.row());
    }

    result.validationRuleIndices = validationRuleIndices;
    presenter->fieldEncoderConfigurationDialogConfirmed(result);
}

void ViewImpl::onMappingEncoderSetOperation(qt_dto::MappingEncoderSetOperation dto) {
    qDebug() << "inside ViewImpl::onMappingEncoderSetOperation";
    qDebug() << dto.value;

    domain::MappingEncoderSetOperation domainOperation;
    domainOperation.excelRowIndex = dto.index.row();
    domainOperation.fieldEncoderIndex = dto.value.toInt();
    presenter->onMappingEncoderSetOperation(domainOperation);
}

void ViewImpl::onSaveFieldMappingsRequested() {
    QString documentsPath = qt_utility::getDocumentsPath(); 
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save field mappings", documentsPath, "JSON (*.json)"
    );

    // user cancelled dialog
    if (fileName.isEmpty()) 
        return;

    qDebug() << "selected file name was " << fileName;

    presenter->saveFieldMappings(fileName.toStdString());
}

void ViewImpl::onLoadFieldMappingsRequested() {
    QString documentsPath = qt_utility::getDocumentsPath(); 
    QString fileName = QFileDialog::getOpenFileName(
        this, "Load field mappings", documentsPath, "JSON (*.json)"
    );

    // user cancelled dialog
    if (fileName.isEmpty()) 
        return;

    presenter->loadFieldMappings(fileName.toStdString());
}

void ViewImpl::infoBox(string message) {
    QMessageBox::information(this, "Information", QString::fromStdString(message));
}

// MASSIVE HACK and MVP VIOLATION -- fieldMappingModel should be changed to use
// a copy of state, not a reference
void ViewImpl::forceRefreshFieldMappings() {
    fieldMappingModel->layoutAboutToBeChanged();
    fieldMappingModel->layoutChanged();
}
