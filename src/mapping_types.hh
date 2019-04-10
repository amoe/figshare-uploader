#ifndef MAPPING_TYPES_HH
#define MAPPING_TYPES_HH

#include <iostream>
#include <vector>
#include <map>
#include "optional.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using nonstd::optional;

// Should be
// using OptionsMap = map<string, optional<string>>;
using OptionsMap = map<string, string>;

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
