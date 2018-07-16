#ifndef CUSTOM_FIELD_MAPPER_HH
#define CUSTOM_FIELD_MAPPER_HH

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class CustomFieldMapper {
public:
    map<string, string> mapCustomFields(const vector<string> excelRow);
};

#endif // CUSTOM_FIELD_MAPPER_HH
