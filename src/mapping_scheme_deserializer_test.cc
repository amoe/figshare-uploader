#include <string>
#include <gmock/gmock.h>
#include "test_vocabulary.hh"
#include "mapping_scheme_deserializer.hh"
#include "mapping_types.hh"
#include "default_field_encoders.hh"

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
                "targetField": {
                    "fieldType": "standard",
                    "name": "title"
                },
                "name": "String",
                "validationRules": [],
                "options": {}
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


const string inputForCategoryEncoder = R"(
    {
        "rows": [
            {
                "targetField": {
                    "fieldType": "standard",
                    "name": "categories"
                },
                "name": "LookupList",
                "validationRules": [],
                "options": {
                    "delimiter": ",\\s*",
                    "resourceName": "category"
                }
            }
        ]
    }
)";

TEST_F(MappingSchemeDeserializerTest, CanDeserializeCategoryEncoder) {
    MappingSchemeDeserializer deserializer;
    MappingScheme expectedResult = {default_field_encoders::CATEGORY_ENCODER};

    MappingScheme actualResult = deserializer.deserialize(inputForCategoryEncoder);
    ASSERT_THAT(actualResult, Eq(expectedResult));
}
