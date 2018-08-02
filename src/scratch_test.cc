#include <gmock/gmock.h>

using namespace testing;

// This is for exploratory tests that may later be moved elsewhere

TEST(ScratchTests, Test1) {
    ASSERT_THAT(2 + 2, Eq(4));
}

