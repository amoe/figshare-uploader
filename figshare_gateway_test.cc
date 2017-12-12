#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "stubs.hh"
#include "raw_literals.hh"

using ::testing::Eq;

TEST(FigshareGatewayTest, ActsAsIExpect) {
    HttpPoster* poster = new StubHttpPoster(
        raw_literals::fakeArticleCreationResponse
    );
    FigshareGateway* gateway = new HttpFigshareGateway(poster);
    
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

    ArticleCreationResponse response = gateway->createArticle(request);

    ASSERT_THAT(response.location, Eq("http://nonexistent.net/"));
}

