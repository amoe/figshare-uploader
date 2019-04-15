#ifndef MAPPING_TYPES_HH
#define MAPPING_TYPES_HH

#include <iostream>
#include <vector>
#include <map>

#include <QJsonObject>
#include "optional.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using nonstd::optional;








// MAPPING OUTPUT TYPES -- These are used as containers during the field mapping
// process, but they should never be serialized.

// FINAL OUTPUT TYPE.
class MappingOutput {
public:
    MappingOutput(
        QJsonObject articleObject, vector<string> sourcePaths
    ): articleObject(articleObject), sourcePaths(sourcePaths) { }

    QJsonObject getArticleObject() const;
    vector<string> getSourcePaths() const;


private:
    QJsonObject articleObject;
    vector<string> sourcePaths;
};

enum class CombinationOperation { CONJOIN };

// INTERMEDIATE OUTPUT TYPE.  It needs to be combined with a MappingOutput and
// a TargetField, by the FieldEncoder's `applyEncoder` method.
class IntermediateMappingOutput {
public:
    IntermediateMappingOutput(
        QJsonValue producedValue, vector<string> producedPaths,
        CombinationOperation operation
    ): producedValue(producedValue), producedPaths(producedPaths), operation(operation) {
    }

    QJsonValue getProducedValue() const;
    vector<string> getProducedPaths() const;
    CombinationOperation getOperation() const;

private:
    QJsonValue producedValue;
    vector<string> producedPaths;
    CombinationOperation operation;
};



// SERIALIZATION TYPES -- These correspond to a certain JSON layout, which was
// conceived in `figshare-cases.ts`.


using OptionsMap = map<string, optional<string>>;

enum class ConverterName { 
    STRING, LIST_OF_OBJECT, LIST_OF_STRING, LOOKUP_LIST, CONTRIBUTE_FILES
};

enum class TargetFieldType { STANDARD, CUSTOM };

enum class ValidationRule {
    REQUIRE_VALID_URL
};

class TargetField {
public:
    TargetField(TargetFieldType type, string name): type(type), name(name) { }
    TargetFieldType getTargetFieldType() const;
    string getName() const;

private:
    TargetFieldType type;
    string name;
};

class FieldEncoder {
public:
    FieldEncoder(
        optional<TargetField> targetField, ConverterName converterName,
        vector<ValidationRule> validationRules,
        OptionsMap options
    ): targetField(targetField),
       converterName(converterName),
       validationRules(validationRules),
       options(options) { }

    ConverterName getConverterName() const;
    OptionsMap getOptions() const;
    optional<TargetField> getTargetField() const;
    vector<ValidationRule> getValidationRules() const;
    
    MappingOutput applyEncoder(MappingOutput seed, IntermediateMappingOutput operand) const;

private:
    optional<TargetField> targetField;
    ConverterName converterName;
    vector<ValidationRule> validationRules;
    OptionsMap options;
};

class RowMapping {
public:
    RowMapping(int sourceRowIndex, FieldEncoder fieldEncoder):
      sourceRowIndex(sourceRowIndex), fieldEncoder(fieldEncoder) { }

    int getSourceRowIndex() const;
    FieldEncoder getFieldEncoder() const;

private:
    int sourceRowIndex;
    FieldEncoder fieldEncoder;
};

using MappingScheme = vector<RowMapping>;


#endif /* MAPPING_TYPES_HH */
