#include <gmock/gmock.h>
#include <vector>
#include <string>
#include "optional.hpp"
#include "mapping_engine.hh"
#include "mapping_types.hh"
#include "test_utility.hh"
#include "test_vocabulary.hh"
#include "default_field_encoders.hh"
#include "mocks.hh"

using nonstd::optional;
using nonstd::nullopt;
using std::vector;
using std::string;

class MappingEngineTest: public Test {
public:
    MappingEngineTest() {
        ConverterRegistry::initializeStandardConverters(converterRegistry, &lookups);
        engine = new MappingEngineImpl(&converterRegistry);
    }
    ~MappingEngineTest() {
        delete engine;
    }

    ConverterRegistry converterRegistry;
    MockLookupRegistry lookups;
    MappingEngine* engine;
};

// It's quite difficult to construct these MappingSchemes in C++ code.
// This isn't to be construed as a feature, but these structures are the full
// definition of the available behaviours.
// There might be more 'sugary' ways to write them that could be constructed
// later.

TEST_F(MappingEngineTest, TitleStringConversionCheck) {
    MappingScheme theScheme = {default_field_encoders::TITLE_ENCODER};

    vector<string> theDocument = {"foo"};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
           "title": "foo"
        }
    )";

    vector<string> expectedSourcePaths = {};

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}


TEST_F(MappingEngineTest, ContributeFilesCheck) {
    vector<string> theDocument = {
        "foo.tiff;bar.tiff"
    };

    MappingScheme theScheme = {
        default_field_encoders::CONTRIBUTE_FILES_ENCODER
    };

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    // Expect an empty article object because we haven't defined any other
    // converters.
    QJsonObject expectedArticle;
    vector<string> expectedSourcePaths = {
        "foo.tiff", "bar.tiff"
    };

    ASSERT_THAT(result.getArticleObject(), Eq(expectedArticle));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}


TEST_F(MappingEngineTest, DefinedTypeLookupListCheck) {
    vector<string> theDocument = {
        "Figure"
    };
    MappingScheme theScheme = {default_field_encoders::DEFINED_TYPE_ENCODER};

    EXPECT_CALL(
        lookups, lookupByString(LookupType::DEFINED_TYPE, _)
    ).WillOnce(Return(QJsonValue("figure")));

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    // Expect an empty article object because we haven't defined any other
    // converters.
    QJsonObject expectedArticle;
    vector<string> expectedSourcePaths = {};

    const string expectedResult = R"(
        {
           "defined_type": "figure"
        }
    )";


    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}

TEST_F(MappingEngineTest, DiscardConverterCheck) {
    MappingScheme theScheme = {default_field_encoders::DISCARD_ENCODER};
    vector<string> theDocument = {"foo"};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
        }
    )";
    vector<string> expectedSourcePaths = {};

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}

TEST_F(MappingEngineTest, KeywordEncoderCheck) {
    MappingScheme theScheme = {default_field_encoders::KEYWORDS_ENCODER};
    vector<string> theDocument = {"foo, bar, baz"};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "keywords": ["foo", "bar", "baz"]
        }
    )";
    vector<string> expectedSourcePaths = {};

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}

TEST_F(MappingEngineTest, KeywordEncoderElidesEmptyString) {
    MappingScheme theScheme = {default_field_encoders::KEYWORDS_ENCODER};
    vector<string> theDocument = {""};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "keywords": []
        }
    )";
    vector<string> expectedSourcePaths = {};

    qDebug() << result.getArticleObject();

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}



TEST_F(MappingEngineTest, ReferencesEncoderCheck) {
    MappingScheme theScheme = {default_field_encoders::REFERENCES_ENCODER};
    vector<string> theDocument = {"foo, bar, baz"};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "references": ["foo, bar, baz"]
        }
    )";
    vector<string> expectedSourcePaths = {};

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}

TEST_F(MappingEngineTest, HandlesBlankReferences) {
    MappingScheme theScheme = {default_field_encoders::REFERENCES_ENCODER};
    vector<string> theDocument = {""};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "references": []
        }
    )";
    vector<string> expectedSourcePaths = {};

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}




TEST_F(MappingEngineTest, CategoryEncoderCheck) {
    MappingScheme theScheme = {default_field_encoders::CATEGORY_ENCODER};
    vector<string> theDocument = {"North American History"};

    EXPECT_CALL(
        lookups, lookupByString(LookupType::CATEGORY, _)
    ).WillOnce(Return(QJsonValue(1703)));

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    // Expect an empty article object because we haven't defined any other
    // converters.
    QJsonObject expectedArticle;
    vector<string> expectedSourcePaths = {};

    const string expectedResult = R"(
        {
           "categories": [1703]
        }
    )";


    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}

TEST_F(MappingEngineTest, HandlesBlankCategories) {
    MappingScheme theScheme = {default_field_encoders::CATEGORY_ENCODER};
    vector<string> theDocument = {""};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "categories": []
        }
    )";
    vector<string> expectedSourcePaths = {};

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}


TEST_F(MappingEngineTest, LicenseEncoderCheck) {
    MappingScheme theScheme = {default_field_encoders::LICENSE_ENCODER};
    vector<string> theDocument = {"CC0"};

    EXPECT_CALL(
        lookups, lookupByString(LookupType::LICENSE, _)
    ).WillOnce(Return(QJsonValue(42)));

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    // Expect an empty article object because we haven't defined any other
    // converters.
    QJsonObject expectedArticle;
    vector<string> expectedSourcePaths = {};

    const string expectedResult = R"(
        {
           "license": 42
        }
    )";


    qDebug() << result.getArticleObject();

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}


TEST_F(MappingEngineTest, AuthorsEncoderCheck) {
    MappingScheme theScheme = {default_field_encoders::AUTHORS_ENCODER};
    vector<string> theDocument = {"foo, bar, baz"};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "authors": [
                {"name": "foo"},
                {"name": "bar"},
                {"name": "baz"}
            ]
        }
    )";
    vector<string> expectedSourcePaths = {};

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}

TEST_F(MappingEngineTest, GroupEncoderCheck) {
    MappingScheme theScheme = {default_field_encoders::GROUP_ENCODER};
    vector<string> theDocument = {"The Planet Bethlehem Project"};

    EXPECT_CALL(
        lookups, lookupByString(LookupType::GROUP, _)
    ).WillOnce(Return(QJsonValue(11611)));

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    QJsonObject expectedArticle;
    vector<string> expectedSourcePaths = {};

    const string expectedResult = R"(
        {
           "group_id": 11611
        }
    )";


    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}


TEST_F(MappingEngineTest, CustomFieldEncoderWorks) {

    const FieldEncoder creatorEncoder(
        optional<TargetField>(TargetField(TargetFieldType::CUSTOM, "Creator")),
        ConverterName::STRING,
        {},
        {}
    );
    MappingScheme theScheme = {creatorEncoder};


    vector<string> theDocument = {"foo"};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "custom_fields": {
                "Creator": "foo"
            }
        }
    )";

    vector<string> expectedSourcePaths = {};

    qDebug() << result.getArticleObject();

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}

TEST_F(MappingEngineTest, MultipleCustomFieldEncoderWorks) {
    const FieldEncoder creatorEncoder(
        optional<TargetField>(TargetField(TargetFieldType::CUSTOM, "Creator")),
        ConverterName::STRING,
        {},
        {}
    );

    const FieldEncoder languageEncoder(
        optional<TargetField>(TargetField(TargetFieldType::CUSTOM, "Language")),
        ConverterName::STRING,
        {},
        {}
    );

    MappingScheme theScheme = {creatorEncoder, languageEncoder};


    vector<string> theDocument = {"foo", "English"};

    MappingOutput result = this->engine->convert(theDocument, theScheme);

    const string expectedResult = R"(
        {
            "custom_fields": {
                "Creator": "foo",
                "Language": "English"
            }
        }
    )";

    vector<string> expectedSourcePaths = {};

    qDebug() << result.getArticleObject();

    ASSERT_THAT(result.getArticleObject(), Eq(deserialize(expectedResult)));
    ASSERT_THAT(result.getSourcePaths(), Eq(expectedSourcePaths));
}
