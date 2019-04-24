#include <gmock/gmock.h>
#include "interfaces.hh"
#include "presenter.hh"
#include "test_vocabulary.hh"
#include "mocks.hh"
#include "logging.hh"

class PresenterTest: public Test {
public:
    PresenterTest() {
    }

    MockModel model;
    MockDriver driver;
    MockTokenStore tokenStore;
};


TEST_F(PresenterTest, HandlesNewFieldEncoder) {
    Presenter* presenter = new PresenterImpl(&model, &driver, &tokenStore);

    domain::FieldEncoderListOperation dto;
    dto.index = -1;   // indicates an add
    dto.targetFieldTypeId = 0;
    dto.fieldName = "title2";
    dto.validationRuleIndices = {};
    dto.converterIndex = 1;
    dto.newOptions = {};
    dto.isTargetFieldSet = true;

    TargetField targetField(TargetFieldType::STANDARD, "title2");
    FieldEncoder expectedFieldEncoder(
        optional<TargetField>(targetField),
        ConverterName::STRING,
        {},
        {}
    );


    spdlog::info("Expected: {}", expectedFieldEncoder.describe());
    EXPECT_CALL(model, addFieldEncoder(expectedFieldEncoder));
    presenter->fieldEncoderConfigurationDialogConfirmed(dto);
}

