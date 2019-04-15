#include <stdexcept>
#include "custom_fields.hh"

string CustomFieldDatum::getJsonKey() const {
    return specification.name;
}

QJsonValue CustomFieldDatum::getJsonValue() const {
    switch (specification.encoder) {
        case FieldEncoderOld::STRING: 
            return QJsonValue(QString::fromStdString(content));
        case FieldEncoderOld::LIST: {
            QJsonArray array;
            array.append(QJsonValue(QString::fromStdString(content)));
            return array;
        }
        default:
            throw std::runtime_error("unknown field encoder type");
    }
}


void CustomFieldSet::add(CustomFieldDatum datum) {
    content.push_back(datum);
}

QJsonObject CustomFieldSet::render() const {
    QJsonObject result;

    for (CustomFieldDatum datum: content) {
        QString jsonKey = QString::fromStdString(datum.getJsonKey());
        QJsonValue jsonValue = datum.getJsonValue();

        result.insert(jsonKey, jsonValue);
    }
    
    return result;
}
