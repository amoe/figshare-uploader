#ifndef CUSTOM_FIELD_MAPPER_HH
#define CUSTOM_FIELD_MAPPER_HH

#include <map>
#include <string>
#include <vector>
#include "custom_fields.hh"

using std::map;
using std::string;
using std::vector;

class CustomFieldMapper {
public:
    CustomFieldSet mapCustomFields(const vector<string> excelRow);
};

#endif // CUSTOM_FIELD_MAPPER_HH
