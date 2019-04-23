#include "mapping_scheme_deserializer.hh"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include "qt_utility.hh"

using std::runtime_error;
using qt_utility::safeValue;
using qt_utility::valueToObject;
using qt_utility::valueToArray;

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


// FieldEncoder MappingSchemeDeserializer::deserializeTargetField(QJsonValue value) const {
//     if (value.is
// }
