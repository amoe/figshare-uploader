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

TEST(CustomFieldSupport, supportsContributors) {
    CustomFieldMapper myMapper;

    const string contributorsValue = "American Colony (Jerusalem). Photo Dept., photographer";

    vector<string> row(column_mapping::MAX_FIELD, "");
    row.at(column_mapping::CONTRIBUTORS) = contributorsValue;

    map<string, string> result = myMapper.mapCustomFields(row);
    
    map<string, string> expected = {
        {"Contributors", contributorsValue}
    };

    ASSERT_THAT(result, Eq(expected));
}


// TEST(CustomFieldSupport, supportsProject) {
//     CustomFieldMapper myMapper;

//     const string projectValue = "http://www.figshare.com/project/foo";

//     vector<string> row(column_mapping::MAX_FIELD, "");
//     row.at(column_mapping::CONTRIBUTORS) = contributorsValue;

//     map<string, string> result = myMapper.mapCustomFields(row);
    
//     map<string, string> expected = {
//         {"Contributors", contributorsValue}
//     };

//     ASSERT_THAT(result, Eq(expected));
// }


// TEST(CustomFieldSupport, supportsCollection) {
//     CustomFieldMapper myMapper;

//     const string collectionsValue = "http://www.figshare.com/collection/bar";

//     vector<string> row(22, "");
//     row.at(column_mapping::CONTRIBUTORS) = contributorsValue;

//     map<string, string> result = myMapper.mapCustomFields(row);
    
//     map<string, string> expected = {
//         {"Contributors", contributorsValue}
//     };

//     ASSERT_THAT(result, Eq(expected));
// }

