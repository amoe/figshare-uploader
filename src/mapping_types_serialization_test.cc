#include <gmock/gmock.h>
#include "mapping_types.hh"
#include "mapping_scheme_serializer.hh"
#include "test_utility.hh"
#include <QDebug>

using ::testing::Eq;

TEST(MappingTypesSerializationTest, CanSerializeMappingScheme) {
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

