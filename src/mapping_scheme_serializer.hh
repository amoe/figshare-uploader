#ifndef MAPPING_SCHEME_SERIALIZER_HH
#define MAPPING_SCHEME_SERIALIZER_HH

#include <QJsonObject>
#include "optional.hpp"
#include "mapping_types.hh"

class MappingSchemeSerializer {
public:
    QJsonObject serialize(MappingScheme input) const;
    void saveMappingScheme(MappingScheme mappingScheme, string outputPath) const;

private:
    QJsonValue serializeFieldEncoder(FieldEncoder f) const;
    QJsonValue serializeTargetField(optional<TargetField> t) const;
    QJsonValue mapTargetFieldType(TargetFieldType t) const;
    QJsonValue mapConverterName(ConverterName c) const;
    QJsonValue serializeValidationRules(vector<ValidationRule> rules) const;
    QJsonValue serializeOptions(OptionsMap options) const;
};


#endif /* MAPPING_SCHEME_SERIALIZER_HH */
