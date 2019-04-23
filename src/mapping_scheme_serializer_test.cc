#include <QDebug>
#include <gmock/gmock.h>
#include "mapping_types.hh"
#include "mapping_scheme_serializer.hh"
#include "test_utility.hh"
#include "default_field_encoders.hh"
#include "test_vocabulary.hh"

const string expectedResultForDiscardEncoder = R"(
    {
        "rows": [
            {
                "targetField": null,
                "name": "Discard",
                "validationRules": [],
                "options": {}
            }
        ]
    }
)";


TEST(MappingSchemeSerializerTest, CanSerializeDiscardEncoder) {
    MappingScheme theScheme = {default_field_encoders::DISCARD_ENCODER};
    MappingSchemeSerializer serializer;
    QJsonObject result = serializer.serialize(theScheme);
    qDebug() << result;
    ASSERT_THAT(result, Eq(deserialize(expectedResultForDiscardEncoder)));
}

TEST(MappingSchemeSerializerTest, CanSerializeMappingSchemeWithTitleEncoder) {
    // Create a simple scheme
    TargetField targetField(TargetFieldType::STANDARD, "title");
    FieldEncoder titleEncoder(
        optional<TargetField>(targetField),
        ConverterName::STRING,
        {},
        {}
    );
    MappingScheme theScheme = {titleEncoder};

    MappingSchemeSerializer serializer;

    const string expectedResult = R"(
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


    QJsonObject result = serializer.serialize(theScheme);

    qDebug() << result;

    ASSERT_THAT(result, Eq(deserialize(expectedResult)));
}


const string expectedResultForCategoryEncoder = R"(
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
                    "delimiter": null,
                    "resourceName": "category"
                }
            }
        ]
    }
)";


// The category encoder is chosen because it exercises the various quirks
// of the serialization format.
TEST(MappingSchemeSerializerTest, CanSerializeMappingSchemeWithCategoryEncoder) {
    MappingScheme theScheme = {default_field_encoders::CATEGORY_ENCODER};

    MappingSchemeSerializer serializer;
    QJsonObject result = serializer.serialize(theScheme);

    qDebug() << result;

    ASSERT_THAT(result, Eq(deserialize(expectedResultForCategoryEncoder)));
}


