#include <gmock/gmock.h>
#include "interfaces.hh"
#include "presenter.hh"
#include "test_vocabulary.hh"
#include "mocks.hh"


class PresenterTest: public Test {
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

    domain::FieldEncoderListOperation dto;
    dto.index = -1;   // indicates an add
    dto.targetFieldTypeId = 0;
    dto.fieldName = "title2";
    dto.validationRuleIndices = {};
    dto.converterIndex = 1;
    dto.newOptions = {};

    TargetField targetField(TargetFieldType::STANDARD, "title2");
    FieldEncoder expectedFieldEncoder(
        optional<TargetField>(targetField),
        ConverterName::STRING,
        {},
        {}
    );


    // Something is going very wrong here, this is a nasty heisenbug!
    // std::cout << "Expected: " << expectedFieldEncoder.describe() << std::endl;
    EXPECT_CALL(model, addFieldEncoder(expectedFieldEncoder));
    presenter->fieldEncoderConfigurationDialogConfirmed(dto);
}

