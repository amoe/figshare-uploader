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

    vector<string> row(20, "");
    row.at(column_mapping::CONTRIBUTORS) = "American Colony (Jerusalem). Photo Dept., photographer";

    map<string, string> result = myMapper.mapCustomFields(row);
    
    ASSERT_THAT(2 + 2, Eq(5));
}

