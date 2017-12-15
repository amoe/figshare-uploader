#include <gmock/gmock.h>

using ::testing::Eq;

TEST(DriverTest, ActsAsIExpect) {
    ASSERT_THAT(2 + 2, Eq(4));
}


