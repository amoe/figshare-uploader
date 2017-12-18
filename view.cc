#include <QObject>
#include <QDebug>
#include <QPlainTextEdit>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "view.hh"
#include "presenter.hh"
#include "slot_adapter.hh"

ViewImpl::ViewImpl(Presenter* presenter) : QWidget(0, Qt::Window), presenter(presenter) {
    // layout MUST be allocated on the heap here, if it goes out of scope, it
    // will simply stop layout out the widgets properly!
    // But, I think that we don't need to clean it up because the QWidget
    // destructor will delete it at the appropriate time.
    QGridLayout* layout = new QGridLayout(this);


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
    layout->addWidget(logger, 3, 0, 1, 12);

    setLayout(layout);

    SlotAdapter slotAdapter(presenter, &Presenter::startUpload);

    connect(
        this->actionButton,
        &QPushButton::released,
        slotAdapter
    );
}

std::string ViewImpl::getSelectedFile() {
    QString content = selectedFile->text();
    return content.toStdString();
}

void ViewImpl::reportError(std::string errorText) {
    QString qErrorText = QString::fromStdString(errorText);
    QMessageBox::critical(this, "Error", qErrorText);
}

void ViewImpl::addLog(std::string logText) {
    QString newLog = logger->toPlainText() + "\n" + QString::fromStdString(logText);
    logger->setPlainText(newLog);
}
