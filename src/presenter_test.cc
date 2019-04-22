#include <gmock/gmock.h>
#include "interfaces.hh"
#include "presenter.hh"
#include "test_vocabulary.hh"

class PresenterTest: public Test {
};

class MockModel: public Model {
public:
    MOCK_METHOD1(setSourceFile, void(string));
    MOCK_METHOD0(getAvailableEncoders, vector<FieldEncoder>&());
    MOCK_METHOD1(addFieldEncoder, void(FieldEncoder));
    MOCK_METHOD2(bindRow, void(int, int));
    MOCK_METHOD1(setHeaderFields, void(vector<string>));
    MOCK_CONST_METHOD0(getFieldMappings, const MappingScheme&());
    MOCK_CONST_METHOD0(getSourceFile, const optional<string>());
    MOCK_CONST_METHOD0(getHeaderFields, const vector<string>());
    MOCK_CONST_METHOD0(getConverterRegistry, const ConverterRegistry&());
    MOCK_CONST_METHOD0(dumpMappingScheme, void());
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


    TargetField targetField(TargetFieldType::STANDARD, "title2");
    FieldEncoder expectedFieldEncoder(
        optional<TargetField>(targetField),
        ConverterName::STRING,
        {},
        {}
    );

    EXPECT_CALL(model, addFieldEncoder(expectedFieldEncoder));
    presenter->fieldEncoderConfigurationDialogConfirmed(dto);
}

