#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "stubs.hh"
#include "raw_literals.hh"

using ::testing::Eq;

TEST(FigshareGatewayTest, ActsAsIExpect) {
    HttpGetter* getter = new StubHttpGetter("You should not see this");

    HttpPoster* poster = new StubHttpPoster(
        raw_literals::fakeArticleCreationResponse
    );
    HttpPutter* putter = new StubHttpPutter("You should also not see this");

    CategoryMapper categoryMapper(raw_literals::categoryResponse);
    FigshareGateway* gateway = new HttpFigshareGateway(
        getter, poster, putter, categoryMapper
    );
    
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
        1,
        {},
        "Some group",
        {}
    );

    ArticleCreationResponse response = gateway->createArticle(request);

    ASSERT_THAT(response.location, Eq("http://nonexistent.net/"));
}

