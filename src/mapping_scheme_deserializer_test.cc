#include <string>
#include <gmock/gmock.h>
#include "test_vocabulary.hh"
#include "mapping_scheme_deserializer.hh"
#include "mapping_types.hh"

using std::string;

class MappingSchemeDeserializerTest: public Test {
};

const string inputEmpty = R"(
    {
        "rows": [
        ]
    }
)";



TEST_F(MappingSchemeDeserializerTest, CanDeserializeEmptyScheme) {
    MappingSchemeDeserializer deserializer;

    MappingScheme expectedResult;
    MappingScheme actualResult = deserializer.deserialize(inputEmpty);

    ASSERT_THAT(actualResult, Eq(expectedResult));
}


const string inputTitleEncoder = R"(
    {
        "rows": [
            {
                "sourceRowIndex": 0,
                "fieldEncoder": {
                    "targetField": {
                        "fieldType": "standard",
                        "name": "title"
                    },
                    "name": "String",
                    "validationRules": [],
                    "options": {}
                }
            }
        ]
    }
)";



TEST_F(MappingSchemeDeserializerTest, CanDeserializeSingleTitleEncoder) {
    MappingSchemeDeserializer deserializer;

    MappingScheme expectedResult = {
        FieldEncoder(
            optional<TargetField>(TargetField(TargetFieldType::STANDARD, "title")),
            ConverterName::STRING,
            {},
            {}
        )
    };

    MappingScheme actualResult = deserializer.deserialize(inputTitleEncoder);

    ASSERT_THAT(actualResult, Eq(expectedResult));
}

