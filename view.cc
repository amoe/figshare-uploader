#include <QObject>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include "view.hh"
#include "presenter.hh"

View::View(Presenter presenter) : QWidget(0, Qt::Window), presenter(presenter) {
    // layout MUST be allocated on the heap here, if it goes out of scope, it
    // will simply stop layout out the widgets properly!

    QGridLayout* layout = new QGridLayout;

    this->selectedFile = new QLineEdit(this);
    layout->addWidget(this->selectedFile, 0, 0);

    this->actionButton = new QPushButton("Push me", this);
    layout->addWidget(this->actionButton, 1, 0);

    setLayout(layout);
}

std::string View::getSelectedFile() const {
    QString content = selectedFile->text();
    return content.toStdString();
}