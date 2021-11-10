#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "stubs.hh"
#include "raw_literals.hh"
#include "group_mapper.hh"
#include "test_utility.hh"
#include "mocks.hh"

using namespace testing;

TEST(FigshareGatewayTest, CanPostArticle) {
    HttpGetter* getter = new StubHttpGetter("You should not see this");

    HttpPoster* poster = new StubHttpPoster(
        raw_literals::fakeArticleCreationResponse
    );
    HttpPutter* putter = new StubHttpPutter("You should also not see this");

    CategoryMapper categoryMapper(raw_literals::categoryResponse);

    // This is really just a fancier way of using the stub objects above.
    MockHttpGetter httpGetter;
    GroupMapperImpl groupMapper(&httpGetter);

    // XXX: Many of these mappers are not actually used anymore, post the
    // mapping engine refactor.
    FigshareGateway* gateway = new HttpFigshareGateway(
        getter, poster, putter, categoryMapper, &groupMapper
    );

    const string fakeArticle = R"(
        {
           "title": "foo"
        }
    )";
    QJsonObject articleObject = deserialize(fakeArticle);
    ArticleCreationResponse response = gateway->createArticle(articleObject);

    ASSERT_THAT(response.location, Eq("http://nonexistent.net/"));
}

