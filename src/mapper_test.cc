#include <gmock/gmock.h>
#include "requests.hh"
#include "test_utility.hh"
#include "raw_literals.hh"
#include "article_types.hh"
#include "article_type_mapper.hh"
#include "article_mapper.hh"
#include "utility.hh"
#include "object_mother.hh"
#include "column_mapping.hh"

using nonstd::optional;
using nonstd::nullopt;

using ::testing::Eq;
using ::testing::StartsWith;
using ::testing::EndsWith;

TEST(ArticleMapperTest, HandlesBlankReferencesCorrectly) {
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    ArticleMapperImpl myMapper(typeMapper, categoryMapper);

    // fill up the whole row with blanks
    vector<string> row(20, "");

    // Superfluously ensure that category is also blank
    row.at(column_mapping::REFERENCES) = "";

    ArticleCreationRequest request = myMapper.mapFromExcel(row);

    vector<string> expectedReferences = {};

    ASSERT_THAT(request.getReferences(), Eq(expectedReferences));
}

TEST(ArticleMapperTest, HandlesBlankCategoriesCorrectly) {
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    ArticleMapperImpl myMapper(typeMapper, categoryMapper);


    // fill up the whole row with blanks
    vector<string> row(20, "");

    // Superfluously ensure that category is also blank
    row.at(2) = "";

    ArticleCreationRequest request = myMapper.mapFromExcel(row);

    vector<int> expectedCategories = {};

//    ASSERT_THAT(request.getCategories(), Eq(expectedCategories));
}


TEST(ArticleMapperTest, HandlesMediaTypeCorrectly) {
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    ArticleMapperImpl myMapper(typeMapper, categoryMapper);


    // fill up the whole row with blanks
    vector<string> row(20, "");

    // Superfluously ensure that category is also blank
    row.at(3) = "Figure";

    ArticleCreationRequest request = myMapper.mapFromExcel(row);

    ASSERT_THAT(request.getArticleType(), Eq(ArticleType::FIGURE));
}

TEST(ArticleMapperTest, HandlesKeywordsCorrectly) {
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    ArticleMapperImpl myMapper(typeMapper, categoryMapper);


    // fill up the whole row with blanks
    vector<string> row(20, "");

    // strange lvalue shit
    row.at(4) = "Bethlehem Crafts, Olive Wood, Mother-of-pearl";

    ArticleCreationRequest request = myMapper.mapFromExcel(row);

    vector<string> expectedKeywords;
    expectedKeywords = {"Bethlehem Crafts", "Olive Wood", "Mother-of-pearl"};

    ASSERT_THAT(request.getKeywords(), Eq(expectedKeywords));
}

TEST(ArticleMapperTest, CorrectlyMapsRow) {
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    ArticleMapperImpl myMapper(typeMapper, categoryMapper);

    vector<string> row = {
        "To Serve Man",
        "Freja Howat-Maxted, Jacob Norris, Leila Sansour",
        "Middle Eastern and African History",
        "Figure",
        "Bethlehem Crafts",
        R"(This is a digital reproduction of a black and white photographic print held in the Library of Congress.

Olive wood carving is an ancient tradition in Palestine that continues to the present day. It involves the skillful chiseling of olive wood and is most common in the Bethlehem region. The trade of olive wood ties in more broadly to the fact that the olive tree is symbolic for Palestinians; the olive tree is connected to the earth, they affirm Palestinian roots in the land.

Bethlehem merchants were already trading in locally produced religious devotional objects from olive wood and had identified their potential value in foreign markets from as early as the 1690s. However, it wan't until the late 19th, early 20th centuries that the material experienced a boom and played a part in the global circulation of Bethlehem's souvenir industry. Olive wood continues to be used in the production of souvenirs within the region today.

Taken in the early 20th century, the image exists as part of a wider series produced of traditional dress and people living in the area by G. Eric Matson.

This image exists as part of the Bethlehem Crafts collection in the Planet Bethlehem Archive.)",
        "https://www.loc.gov/item/mpc2004001373/PP/",
        "",    // funding
        "CC BY 4.0",
        "",    // creator
        "American Colony (Jerusalem). Photo Dept., photographer",
        "c.1900-1920",
        "Digital scan of image: 1 negative : glass, stereograph, dry plate ; 5 x 7 in.",
        "Library of Congress, Washington DC, USA, Prints & Photographs Division, reproduction number: LC-DIG-matpc-01281 (digital file from original photo)",
        "English",
        "pb_lc_bcr_c18980000-0004aa.tiff",
        "",    // temporal
        "31.7053804, 35.1849329",
        "Place associated, place of production",
        "pb_lc_bcr_c19000000-0001aa.tiff",
        "Library of Congress. No known restrictions on publication."
    };


    ArticleCreationRequest request = myMapper.mapFromExcel(row);

    ASSERT_THAT(request.getTitle(), Eq("To Serve Man"));
    ASSERT_THAT(request.getDescription(), StartsWith("This is a digital "));
    ASSERT_THAT(request.getDescription(), EndsWith("Planet Bethlehem Archive."));

    vector<string> expectedAuthors;
    expectedAuthors.push_back("Freja Howat-Maxted");
    expectedAuthors.push_back("Jacob Norris");
    expectedAuthors.push_back("Leila Sansour");
    ASSERT_THAT(request.getAuthors(), Eq(expectedAuthors));

    vector<string> expectedKeywords;
    expectedKeywords.push_back("Bethlehem Crafts");
    ASSERT_THAT(request.getKeywords(), Eq(expectedKeywords));

    vector<int> expectedCategories = {1703};
    ASSERT_THAT(request.getCategories(), Eq(expectedCategories));

    vector<string> expectedReferences;
    expectedReferences.push_back("https://www.loc.gov/item/mpc2004001373/PP/");

    ASSERT_THAT(request.getReferences(), Eq(expectedReferences));
}



TEST(ArticleCreationRequestTest, SerializesToJson) {
    vector<string> keywords;
    keywords.push_back("Bethlehem");
    keywords.push_back("Crafts");

    vector<string> references;
    references.push_back("https://www.loc.gov/item/mpc2004001373/PP/");

    vector<int> categories;
    categories.push_back(1703);

    vector<string> authors;
    authors.push_back("Freja Howat-Maxted");

    ArticleCreationRequest request(
        "To Serve Man",
        "Some description",
        keywords,
        references,
        categories,
        authors,
        optional<string>("Some grant number"),
        ArticleType::FIGURE,
        1
    );
    
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    ArticleMapperImpl myMapper(typeMapper, categoryMapper);


    string serializedResult = myMapper.mapToFigshare(request);

    std::cout << serializedResult << std::endl;

    ASSERT_THAT(
        deserialize(serializedResult),
        Eq(deserialize(raw_literals::expectedResult))
    );
}

TEST(ArticleCreationRequestTest, DoesNotSerializeFundingWhenNotProvided) {
    ArticleCreationRequest request = ObjectMother::makeArticleCreationRequest();
    
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    ArticleMapperImpl myMapper(typeMapper, categoryMapper);

    string serializedResult = myMapper.mapToFigshare(request);

    std::cout << serializedResult << std::endl;

    ASSERT_THAT(
        containsKey(serializedResult, "funding"),
        Eq(false)
    );
}


