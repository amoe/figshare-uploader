#include <QDebug>
#include <QWidget>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPixmap>
#include "about_dialog.hh"
#include "version.hh"

const char *foo = "Figshare Uploader\n"
"bar\n"
"baz\n";

const char* title = "<strong>Figshare Uploader</strong>";
const char* copyright = "Copyright © 2019 University of Sussex";
const char* license = "Licensed under the Apache 2.0 License.";
const char* url = "http://github.com/amoe/figshare-uploader";


AboutDialog::AboutDialog(QWidget* parent): QDialog(parent) { 
    qDebug() << "inside about dialog";

    QVBoxLayout* vbox = new QVBoxLayout(this);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    QPixmap pixmap(":/resources/SHL_5_Violet_on_Grass.svg");
    QLabel* pixmapLabel = new QLabel(this);
    pixmapLabel->setPixmap(pixmap);
    pixmapLabel->setAlignment(Qt::AlignHCenter);

    QLabel* titleLabel = new QLabel(this);
    titleLabel->setTextFormat(Qt::RichText);
    titleLabel->setText(title);

    QLabel* versionLabel = new QLabel(versionString, this);

    QLabel* urlLabel = new QLabel(this);
    urlLabel->setTextFormat(Qt::RichText);
    urlLabel->setText(getRichTextUrl(url));


    QLabel* copyrightLabel = new QLabel(copyright, this);
    QLabel* licenseLabel = new QLabel(license, this);

    vbox->addWidget(titleLabel);
    vbox->addWidget(versionLabel);
    vbox->addWidget(urlLabel);
    vbox->addWidget(pixmapLabel);
    vbox->addWidget(copyrightLabel);
    vbox->addWidget(licenseLabel);
    vbox->addSpacing(16);
    vbox->addWidget(buttonBox);

    setLayout(vbox);
}


QString AboutDialog::getRichTextUrl(QString url) const {
    return QString("<a href=\"%1\">%1</a>").arg(url);
}
