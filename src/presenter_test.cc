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
    dto.fieldName = "title2";
    dto.validationRuleIndices = {};
    dto.converterIndex = 0;


    TargetField targetField(TargetFieldType::STANDARD, "title2");
    FieldEncoder expectedFieldEncoder(
        optional<TargetField>(targetField),
        ConverterName::STRING,
        {},
        {}
    );

    // You need to be able to compare these, to be able to test them.
    EXPECT_CALL(model, addFieldEncoder(expectedFieldEncoder));
    presenter->fieldEncoderConfigurationDialogConfirmed(dto);

    //optional<TargetField> targetField = nullopt
    // ConverterName converterName;
    // vector<ValidationRule> validationRules;
    // OptionsMap options;
    // FieldEncoder expectedFieldEncoder(

    // // It should be calling a method on the model, addFieldEncoder();
}

