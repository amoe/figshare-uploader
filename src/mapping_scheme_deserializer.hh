#ifndef MAPPING_SCHEME_DESERIALIZER_HH
#define MAPPING_SCHEME_DESERIALIZER_HH

#include "mapping_types.hh"

class MappingSchemeDeserializer {
public:
    MappingSchemeDeserializer() { }

    MappingScheme deserialize(string input) const;

private:
    FieldEncoder deserializeEncoder(QJsonObject object) const;

    optional<TargetField> deserializeTargetField(QJsonValue value) const;
    ConverterName deserializeConverterName(QJsonValue value) const;
    vector<ValidationRule> deserializeValidationRules(QJsonValue value) const;
    OptionsMap deserializeOptions(QJsonValue value) const;
};


#endif /* MAPPING_SCHEME_DESERIALIZER_HH */
