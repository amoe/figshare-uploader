#include <QDebug>
#include <QWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPixmap>
#include "about_dialog.hh"

AboutDialog::AboutDialog(QWidget* parent): QDialog(parent) { 
    qDebug() << "inside about dialog";

    QVBoxLayout* vbox = new QVBoxLayout(this);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    QPixmap pixmap(":/resources/SHL_5_Violet_on_Grass.svg");
    QLabel* label = new QLabel(this);
    label->setPixmap(pixmap);

    vbox->addWidget(label);
    vbox->addWidget(buttonBox);
    setLayout(vbox);
}

