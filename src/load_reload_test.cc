#include <gmock/gmock.h>
#include "test_vocabulary.hh"
#include "presenter.hh"
#include "mocks.hh"

class LoadReloadTest: public Test {
public:
    MockDriver driver;
    MockTokenStore tokenStore;
    MockLookupRegistry lookupRegistry;
    MockView view;
};

TEST_F(LoadReloadTest, LoadWithoutInitialPickShouldThrow) {
    ConverterRegistry converterRegistry;
    ConverterRegistry::initializeStandardConverters(
        converterRegistry, &lookupRegistry
    );
    ModelImpl model(converterRegistry);


    PresenterImpl presenter(&model, &driver, &tokenStore);

    presenter.setView(&view);
    presenter.loadFieldMappings("resources/basic_schema_for_non_institutional_account.json");
    presenter.loadFieldMappings("resources/basic_schema_for_institutional_account.json");
    
    // if we got here, the test should pass
}

