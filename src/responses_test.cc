#include <gmock/gmock.h>
#include "raw_literals.hh"
#include "responses.hh"
#include "test_vocabulary.hh"

TEST(ResponsesTest, ArticleGetResponseDeserializesCorrectly) {
    ArticleGetResponse response = ArticleGetResponse::fromJson(
        raw_literals::serializedArticleGetResponse
    );

    ASSERT_THAT(response.id, Eq(5702185));
}

