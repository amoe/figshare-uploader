#include <QObject>
#include <QWidget>
#include <QString>
#include <QGridLayout>
#include "view.hh"

View::View() : QWidget(0, Qt::Window) {
    QGridLayout layout;

    this->selectedFile = new QLineEdit(this);
    layout.addWidget(this->selectedFile, 0, 0);
    setLayout(&layout);
}

std::string View::getSelectedFile() const {
    QString content = selectedFile->text();
    return content.toStdString();
}
