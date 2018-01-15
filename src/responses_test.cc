#include <gmock/gmock.h>
#include "raw_literals.hh"
#include "responses.hh"

using ::testing::Eq;

TEST(ResponsesTest, ArticleGetResponseDeserializesCorrectly) {
    ArticleGetResponse response = ArticleGetResponse::fromJson(
        raw_literals::serializedArticleGetResponse
    );

    ASSERT_THAT(response.id, Eq(5702185));
}

