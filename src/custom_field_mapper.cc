#include "custom_field_mapper.hh"
#include "column_mapping.hh"


map<string, string> CustomFieldMapper::mapCustomFields(const vector<string> excelRow) {
    map<string, string> result;

    for (
        auto iter = column_mapping::CUSTOM_FIELDS.begin();
        iter != column_mapping::CUSTOM_FIELDS.end();
        iter++
    ) {
        string apiCustomFieldName = iter->first;
        int rowIndex = iter->second;

        result.insert({apiCustomFieldName, excelRow.at(rowIndex)});
    }

    return result;
}
