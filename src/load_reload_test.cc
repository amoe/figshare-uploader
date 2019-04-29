#include <gmock/gmock.h>
#include "test_vocabulary.hh"
#include "presenter.hh"
#include "mocks.hh"

class LoadReloadTest: public Test {
public:
    MockDriver driver;
    MockTokenStore tokenStore;
    MockLookupRegistry lookupRegistry;
};

TEST_F(LoadReloadTest, LoadWithoutInitialPickShouldThrow) {
    ConverterRegistry converterRegistry;
    ConverterRegistry::initializeStandardConverters(
        converterRegistry, &lookupRegistry
    );
    ModelImpl model(converterRegistry);


    PresenterImpl presenter(&model, &driver, &tokenStore);
    presenter.loadFieldMappings("resources/basic_schema_for_institutional_account.json");


    // this problem happens because we don't set the view properly
    
    ASSERT_THAT(2 + 2, Eq(5));
}

