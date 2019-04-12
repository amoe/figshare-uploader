#include <gmock/gmock.h>
#include <vector>
#include <string>
#include "optional.hpp"
#include "mapping_engine.hh"
#include "mapping_types.hh"
#include "test_utility.hh"


using ::testing::Test;
using ::testing::Eq;
using nonstd::optional;
using nonstd::nullopt;
using std::vector;
using std::string;

class MappingEngineTest: public Test {
public:
    MappingEngineTest() { }
};

// It's quite difficult to construct these MappingSchemes in C++ code.
// This isn't to be construed as a feature, but these structures are the full
// definition of the available behaviours.
// There might be more 'sugary' ways to write them that could be constructed
// later.

TEST_F(MappingEngineTest, TitleStringConversionCheck) {
    // Create a simple scheme
    TargetField targetField(TargetFieldType::STANDARD, "title");
    FieldEncoder titleEncoder(
        optional<TargetField>(targetField),
        ConverterName::STRING,
        {},
        {}
    );
    MappingScheme theScheme = {RowMapping(0, titleEncoder)};

    vector<string> theDocument = {"foo"};

    MappingEngine engine;
    MappingOutput result = engine.convert(theDocument, theScheme);

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
    OptionsMap options = {
        {"delimiter", optional<string>(";")}
    };

    FieldEncoder contributeFilesEncoder(
        nullopt,
        ConverterName::CONTRIBUTE_FILES,
        {},
        options
    );
    MappingScheme theScheme = {RowMapping(0, contributeFilesEncoder)};

    MappingEngine engine;
    MappingOutput result = engine.convert(theDocument, theScheme);

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
    OptionsMap options = {
        {"resourceName", optional<string>("definedType")}
    };

    FieldEncoder lookupListEncoder(
        optional<string>("defined_type"),
        ConverterName::LOOKUP_LIST,
        {},
        options
    );
    MappingScheme theScheme = {RowMapping(0, contributeFilesEncoder)};

    MappingEngine engine;
    MappingOutput result = engine.convert(theDocument, theScheme);

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
