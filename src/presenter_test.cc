#include <gmock/gmock.h>
#include "interfaces.hh"
#include "presenter.hh"
#include "test_vocabulary.hh"

class PresenterTest: public Test {
};

class MockModel: public Model {
public:
    // XXX: Can we remove the f?
    MOCK_METHOD1(setSourceFile, void(string newSourceFile));
    MOCK_METHOD0(getAvailableEncoders, vector<FieldEncoder>&());
    MOCK_METHOD1(addFieldEncoder, void(FieldEncoder f));
    MOCK_CONST_METHOD0(getSourceFile, optional<string>());
};

TEST_F(PresenterTest, HandlesNewFieldEncoder) {
    // Set up the presenter with some mocked out collaborators.
    // Check that it makes the right calls on the model.

    // Mock this out to run call assertions on it.
    MockModel model;

    // Don't need to bother with these.
    Driver* driver;
    TokenStore* tokenStore;

    Presenter* presenter = new PresenterImpl(&model, driver, tokenStore);

    FieldEncoderDomainDTO dto;
    dto.index = -1;   // indicates an add
    dto.targetFieldTypeId = 0;
    dto.fieldName = "title";
    dto.validationRuleIndices = {};
    dto.converterIndex = 0;

    // EXPECT_CALL(model, addFieldEncoder(expectedFieldEncoder));
    // EXPECT_CALL(model, addFieldEncoder(_));
    presenter->fieldEncoderConfigurationDialogConfirmed(dto);

    //optional<TargetField> targetField = nullopt
    // ConverterName converterName;
    // vector<ValidationRule> validationRules;
    // OptionsMap options;
    // FieldEncoder expectedFieldEncoder(

    // // It should be calling a method on the model, addFieldEncoder();
}

