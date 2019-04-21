#include <gmock/gmock.h>
#include <vector>
#include <string>
#include "optional.hpp"
#include "mapping_engine.hh"
#include "mapping_types.hh"
#include "test_utility.hh"
#include "test_vocabulary.hh"
#include "default_field_encoders.hh"

using nonstd::optional;
using nonstd::nullopt;
using std::vector;
using std::string;

class MockLookupRegistry: public LookupRegistry {
public:
    MOCK_METHOD2(lookupByString, QJsonValue(LookupType, string));
};

class MappingEngineTest: public Test {
public:
    MappingEngineTest() {
        engine = new MappingEngine(&lookups);
    }
    ~MappingEngineTest() {
        delete engine;
    }

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
