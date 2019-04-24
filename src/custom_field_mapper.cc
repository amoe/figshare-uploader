#include "custom_field_mapper.hh"
#include "column_mapping.hh"
#include "utility.hh"
#include "logging.hh"

CustomFieldSet CustomFieldMapper::mapCustomFields(const vector<string> excelRow) {
    for (auto col: excelRow) {
        spdlog::info("column: {}", col);
    }

    CustomFieldSet result;

    for (CustomFieldSpecification specification: column_mapping::CUSTOM_FIELDS) {
        string excelRowContent = excelRow.at(specification.position);
        
        if (excelRowContent.empty() || isWhitespaceOnly(excelRowContent))
            continue;

        // construct the new datum, which is copied

        CustomFieldDatum datum(specification, excelRowContent);
        result.add(datum);
    }

    return result;
}
