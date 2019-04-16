#include <gmock/gmock.h>
#include "interfaces.hh"
#include "presenter.hh"

using ::testing::Eq;
using ::testing::Test;

class PresenterTest: public Test {
};

TEST_F(PresenterTest, HandlesNewFieldEncoder) {
    // Set up the presenter with some mocked out collaborators.
    // Check that it makes the right calls on the model.

    // Mock this out to run call assertions on it.
    Model* model;

    // Don't need to bother with these.
    Driver* driver;
    TokenStore* tokenStore;

    Presenter* presenter = new PresenterImpl(model, driver, tokenStore);

    // It should be calling a method on the model, addFieldEncoder();
    ASSERT_THAT(2 + 2, Eq(5));
}

