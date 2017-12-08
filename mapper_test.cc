#include <gmock/gmock.h>
#include "requests.hh"
#include "test_utility.hh"
#include "raw_literals.hh"
#include "article_types.hh"
#include "article_type_mapper.hh"
#include "article_mapper.hh"

using ::testing::Eq;
using ::testing::StartsWith;
using ::testing::EndsWith;

TEST(ArticleMapperTest, CorrectlyMapsRow) {
    ArticleTypeMapper typeMapper;
    ArticleMapper myMapper(typeMapper);


    vector<string> row;
    row.push_back("To Serve Man");
    row.push_back("Freja Howat-Maxted, Jacob Norris, Leila Sansour");
    row.push_back("Middle Eastern and African Library");
    row.push_back("Figure");
    row.push_back("Bethlehem Crafts");
    row.push_back(R"(This is a digital reproduction of a black and white photographic print held in the Library of Congress.

Olive wood carving is an ancient tradition in Palestine that continues to the present day. It involves the skillful chiseling of olive wood and is most common in the Bethlehem region. The trade of olive wood ties in more broadly to the fact that the olive tree is symbolic for Palestinians; the olive tree is connected to the earth, they affirm Palestinian roots in the land.

Bethlehem merchants were already trading in locally produced religious devotional objects from olive wood and had identified their potential value in foreign markets from as early as the 1690s. However, it wan't until the late 19th, early 20th centuries that the material experienced a boom and played a part in the global circulation of Bethlehem's souvenir industry. Olive wood continues to be used in the production of souvenirs within the region today.

Taken in the early 20th century, the image exists as part of a wider series produced of traditional dress and people living in the area by G. Eric Matson.

This image exists as part of the Bethlehem Crafts collection in the Planet Bethlehem Archive.)");


    ArticleCreationRequest request = myMapper.mapFromExcel(row);

    ASSERT_THAT(request.getTitle(), Eq("To Serve Man"));
    ASSERT_THAT(request.getDescription(), StartsWith("This is a digital "));
    ASSERT_THAT(request.getDescription(), EndsWith("Planet Bethlehem Archive."));

    vector<string> expectedAuthors;
    expectedAuthors.push_back("Freja Howat-Maxted");
    expectedAuthors.push_back("Jacob Norris");
    expectedAuthors.push_back("Leila Sansour");

    ASSERT_THAT(request.getAuthors(), Eq(expectedAuthors));
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
    ArticleMapper myMapper(typeMapper);

    string serializedResult = myMapper.mapToFigshare(request);

    std::cout << serializedResult << std::endl;

    ASSERT_THAT(
        deserialize(serializedResult),
        Eq(deserialize(raw_literals::expectedResult))
    );
}


