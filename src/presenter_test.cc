#include <gmock/gmock.h>

using ::testing::Eq;
using ::testing::Test;

class PresenterTest: public Test {
};

TEST_F(PresenterTest, HandlesNewFieldEncoder) {
    // Set up the presenter with some mocked out collaborators.
    // Check that it makes the right calls on the model.
    ASSERT_THAT(2 + 2, Eq(5));
}

