#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QJsonObject>
#include <QDebug>
#include "field_encoder.hh"

ListOfObjectFieldEncoder::ListOfObjectFieldEncoder() {
    this->delimiter = nullptr;
    this->targetFieldName = nullptr;
}

QDialog* ListOfObjectFieldEncoder::makeConfigurationDialog(QWidget* parent) {
    QDialog* result = new QDialog(parent);
//    QPushButton* okButton = new QPushButton("Done");

    QLabel* label1 = new QLabel("Delimiter regex");
    this->delimiter = new QLineEdit;
    QLabel* label2 = new QLabel("Field name within object");
    this->targetFieldName = new QLineEdit;

    QPushButton* ok = new QPushButton("OK");

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(label1, 0, 0);
    grid->addWidget(delimiter, 0, 1);
    grid->addWidget(label2, 1, 0);
    grid->addWidget(targetFieldName, 1, 1);
    grid->addWidget(ok, 2, 0);

    QObject::connect(
        ok,
        &QAbstractButton::clicked,
        result,
        &QDialog::accept
    );

    result->setLayout(grid);

    return result;
}

// Return this encoder serialized as json
QJsonValue ListOfObjectFieldEncoder::asJson() {
    Q_ASSERT(this->delimiter);
    Q_ASSERT(this->targetFieldName);

    QJsonObject object;
    object.insert("delimiter", this->delimiter->text());
    object.insert("targetField", this->targetFieldName->text());
    return object;
}
