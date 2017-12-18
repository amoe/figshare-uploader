#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
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

    this->token = new QLineEdit(this);
    layout->addWidget(this->token, 0, 0);

    this->selectedFile = new QLineEdit(this);
    layout->addWidget(this->selectedFile, 1, 0);

    this->actionButton = new QPushButton("Push me", this);
    layout->addWidget(this->actionButton, 2, 0);

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

