#ifndef FIELD_ENCODER_WIDGET_HH
#define FIELD_ENCODER_WIDGET_HH

#include <QDialog>
#include <QJsonValue>
#include <QLineEdit>

class FieldEncoderWidget {
public:
    virtual QDialog* makeConfigurationDialog(QWidget* parent) = 0;
    virtual QJsonValue asJson() = 0;
};

class ListOfObjectFieldEncoder : public FieldEncoderWidget {
public:
    ListOfObjectFieldEncoder();
    QDialog* makeConfigurationDialog(QWidget* parent);
    QJsonValue asJson();

// FIXME: SRP
private:
    QLineEdit* delimiter;
    QLineEdit* targetFieldName;
};

#endif /* FIELD_ENCODER_HH */
