#include <gmock/gmock.h>

using ::testing::Eq;

TEST(HttpPoster, CanPost) {
    ASSERT_THAT(2 + 2, Eq(4));
}

