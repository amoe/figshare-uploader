#include "mapping_scheme_deserializer.hh"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "qt_utility.hh"

using std::runtime_error;
using qt_utility::safeValue;
using qt_utility::valueToObject;
using qt_utility::valueToArray;
using qt_utility::valueToString;
using nonstd::nullopt;
using nonstd::optional;

MappingScheme MappingSchemeDeserializer::deserialize(string input) const {
    MappingScheme result;

    QJsonDocument document = QJsonDocument::fromJson(
        QString::fromStdString(input).toUtf8()
    );

    QJsonObject rootObject = document.object();

    if (rootObject.isEmpty()) {
        throw new runtime_error("root object seems empty, check format");
    }

    QJsonValue rowsValue = safeValue(rootObject, "rows");
    QJsonArray rowsArray = valueToArray(rowsValue);


    using iter = QJsonArray::const_iterator;
    for (iter it = rowsArray.constBegin(); it != rowsArray.end(); it++) {
        QJsonObject thisValue = valueToObject(*it);
        FieldEncoder thisEncoder = deserializeEncoder(thisValue);
    }

    return result;
}

FieldEncoder MappingSchemeDeserializer::deserializeEncoder(QJsonObject object) const {
    QJsonValue v1 = safeValue(object, "targetField");
    QJsonValue v2 = safeValue(object, "name");
    QJsonValue v3 = safeValue(object, "validationRules");
    QJsonValue v4 = safeValue(object, "options");

    optional<TargetField> targetField = deserializeTargetField(v1);
    ConverterName converterName = deserializeConverterName(v2);
    vector<ValidationRule> validationRules = deserializeValidationRules(v3);
    OptionsMap options = deserializeOptions(v4);

    return FieldEncoder(
        targetField,
        converterName,
        validationRules,
        options
    );
}


optional<TargetField> MappingSchemeDeserializer::deserializeTargetField(
    QJsonValue value
) const {
    optional<TargetField> result;
    
    if (value.isNull()) {
        result = nullopt;
    } else {
        QJsonObject obj = valueToObject(value);
        QString typeSpec = valueToString(safeValue(obj, "fieldType"));
        TargetFieldType type;

        if (typeSpec == "standard") {
            type = TargetFieldType::STANDARD;
        } else if (typeSpec == "custom") {
            type = TargetFieldType::CUSTOM;
        } else {
            throw new runtime_error("unexpected target field type");
        }

        QString fieldName = valueToString(safeValue(obj, "name"));
        
        result = optional<TargetField>(
            TargetField(type, fieldName.toStdString())
        );
    }

    return result;
}

ConverterName MappingSchemeDeserializer::deserializeConverterName(
    QJsonValue value
) const {
    ConverterName result;
    return result;
}

vector<ValidationRule> MappingSchemeDeserializer::deserializeValidationRules(
    QJsonValue value
) const {
    vector<ValidationRule> result;
    return result;
}

OptionsMap MappingSchemeDeserializer::deserializeOptions(QJsonValue value) const {
    OptionsMap result;
    return result;
}
