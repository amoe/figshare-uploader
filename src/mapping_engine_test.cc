#include <gmock/gmock.h>
#include "mapping_engine.hh"
#include "mapping_types.hh"
#include "test_utility.hh"

using ::testing::Test;
using ::testing::Eq;

class MappingEngineTest: public Test {

public:
    MappingEngineTest() { }
};


TEST_F(MappingEngineTest, SanityCheck) {
    // START CREATING TITLE ENCODER

    TargetField targetField(TargetFieldType::STANDARD, "name");
    // Empty options, empty validators.
    FieldEncoder titleEncoder(targetField, Converter::STRING, {}, {});

    // END CREATING TITLE ENCODER
    
    // Bring it together into a scheme.
    MappingScheme theScheme = {RowMapping(0, titleEncoder)};


    vector<string> theDocument = {"foo"};

    MappingEngine engine;
    QJsonObject result = engine.convert(theDocument, theScheme);

    const string expectedResult = R"V0G0N(
        {
           "title": "foo"
        }
    )V0G0N";


    ASSERT_THAT(result, Eq(deserialize(expectedResult)));
}

