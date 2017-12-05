#include <QObject>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include "view.hh"
#include "presenter.hh"

View::View(Presenter presenter) : QWidget(0, Qt::Window), presenter(presenter) {
    QGridLayout layout;

    this->selectedFile = new QLineEdit(this);
    layout.addWidget(this->selectedFile, 0, 0);

    this->actionButton = new QPushButton("Push me", this);
    layout.addWidget(this->actionButton, 1, 0);

    setLayout(&layout);
}

std::string View::getSelectedFile() const {
    QString content = selectedFile->text();
    return content.toStdString();
}
