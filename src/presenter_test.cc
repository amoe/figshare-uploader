#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::Test;

class PresenterTest: public Test {
};

TEST_F(PresenterTest, HandlesNewFieldEncoder) {
    ASSERT_THAT(2 + 2, Eq(5));
}

