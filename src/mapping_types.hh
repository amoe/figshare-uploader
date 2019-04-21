#ifndef MAPPING_TYPES_HH
#define MAPPING_TYPES_HH

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include <QJsonObject>
#include "optional.hpp"
#include "enum_class_hash.hh"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
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

enum class CombinationOperation { CONJOIN, DISCARD };

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
    DISCARD, STRING, LIST_OF_OBJECT, LIST_OF_STRING, LOOKUP_VALUE, 
    CONTRIBUTE_FILES
};

class ConverterNameBijectiveMapper {
public:
    ConverterNameBijectiveMapper() {
        nameToString = {
            {ConverterName::DISCARD, "Discard"},
            {ConverterName::STRING, "String"},
            {ConverterName::CONTRIBUTE_FILES, "ContributeFiles"},
            {ConverterName::LOOKUP_VALUE, "LookupValue"},
            {ConverterName::LIST_OF_STRING, "ListOfString"}
        };

        // invert the map
        for (const auto& pair: nameToString) {
            stringToName.insert({pair.second, pair.first});
        }
    }
    string getSerializableName(ConverterName symbolicName) const {
        return nameToString.at(symbolicName);
    }
    ConverterName getSymbolicName(string serializableName) const {
        return stringToName.at(serializableName);
    }

private:
    unordered_map<ConverterName, string, EnumClassHash> nameToString;
    unordered_map<string, ConverterName> stringToName;
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
    bool operator==(const TargetField& other) const;

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
    string describe() const;
    
    MappingOutput applyEncoder(MappingOutput seed, IntermediateMappingOutput operand) const;

    bool operator==(const FieldEncoder& other) const;

private:
    void handleConjoin(
        QJsonObject& newArticleObject, vector<string>& newSourcePaths,
        IntermediateMappingOutput operand
    ) const;

    optional<TargetField> targetField;
    ConverterName converterName;
    vector<ValidationRule> validationRules;
    OptionsMap options;
};

using MappingScheme = vector<FieldEncoder>;


#endif /* MAPPING_TYPES_HH */
