#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "stubs.hh"
#include "raw_literals.hh"
#include "group_mapper.hh"
#include "mocks.hh"

using namespace testing;

TEST(FigshareGatewayTest, CanConvertArticle) {
    HttpGetter* getter = new StubHttpGetter("You should not see this");

    HttpPoster* poster = new StubHttpPoster(
        raw_literals::fakeArticleCreationResponse
    );
    HttpPutter* putter = new StubHttpPutter("You should also not see this");

    CategoryMapper categoryMapper(raw_literals::categoryResponse);

    // This is really just a fancier way of using the stub objects above.
    MockHttpGetter httpGetter;
    EXPECT_CALL(httpGetter, request(_))
        .WillOnce(Return(raw_literals::groupApiResponse));
    GroupMapperImpl groupMapper(&httpGetter);

    FigshareGateway* gateway = new HttpFigshareGateway(
        getter, poster, putter, categoryMapper, &groupMapper
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
        "The Planet Bethlehem Archive",
        {}
    );

    ArticleCreationResponse response = gateway->createArticle(request);

    ASSERT_THAT(response.location, Eq("http://nonexistent.net/"));
}

