#include <gmock/gmock.h>
#include <map>
#include <vector>
#include "custom_field_mapper.hh"
#include "column_mapping.hh"

using std::map;
using std::vector;
using ::testing::Eq;
using ::testing::StartsWith;
using ::testing::EndsWith;

TEST(CustomFieldSupport, ActsAsIExpect) {
    CustomFieldMapper myMapper;

    const string contributorsValue = "American Colony (Jerusalem). Photo Dept., photographer";

    vector<string> row(20, "");
    row.at(column_mapping::CONTRIBUTORS) = contributorsValue;

    map<string, string> result = myMapper.mapCustomFields(row);
    
    map<string, string> expected = {
        {"Contributors", contributorsValue}
    };
    
    ASSERT_THAT(result, Eq(expected));
}

