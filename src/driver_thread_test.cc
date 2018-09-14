#include <gmock/gmock.h>

using namespace testing;

class DriverThreadTest: public Test {
};

TEST_F(DriverThreadTest, ActsAsIExpect) {
    ASSERT_THAT(2 + 2, Eq(5));
}

