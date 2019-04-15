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
#include "logging.hh"
#include "view.hh"
#include "presenter.hh"
#include "slot_adapter.hh"
#include "settings_dialog.hh"

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


void ViewImpl::showFileDialog() {
    QString documentsPath = 
        QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first();
    QString fileName = QFileDialog::getOpenFileName(
        this, "Open File", documentsPath, "Excel documents (*.xlsx)"
    );

    // We immediately need to delegate back to the presenter, which will call
    // us back later (on changeSourceFile) after storing the chosen filename.
    presenter->fileConfirmed(fileName.toStdString());
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
    debugf("inside about dialog");

    QMessageBox* msgBox = new QMessageBox(
        "Figshare Uploader", versionString, QMessageBox::Information, 0, 0, 0, this
    );
    
    msgBox->setAttribute(Qt::WA_DeleteOnClose);

    QIcon icon = msgBox->windowIcon();
    QSize size = icon.actualSize(QSize(64, 64));

    msgBox->setIconPixmap(icon.pixmap(size));
    msgBox->exec();
}

void ViewImpl::showSettingsDialog(vector<string> headerFields) {
    // Passing 'this' causes rendering fail?  Because SettingsDialog is not
    // a real dialog subclass.
    SettingsDialog* settingsDialog = new SettingsDialog(headerFields, this);

    // We should be setting up the connections here.
    // We should connect to presenter.

    SlotAdapter slotAdapter(presenter, &Presenter::settingsConfirmed);
    connect(settingsDialog, &QDialog::accepted, slotAdapter);

    settingsDialog->show();   // execution semantics of this???
}

