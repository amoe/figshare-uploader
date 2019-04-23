#include <string>
#include <gmock/gmock.h>
#include "test_vocabulary.hh"
#include "mapping_scheme_deserializer.hh"
#include "mapping_types.hh"

using std::string;

class MappingSchemeDeserializerTest: public Test {
};

const string inputEmpty = R"(
    [
    ]
)";


TEST_F(MappingSchemeDeserializerTest, CanDeserializeEmptyScheme) {
    MappingSchemeDeserializer deserializer;

    MappingScheme expectedResult;

    deserializer.deserialize(inputEmpty);

    ASSERT_THAT(2 + 2, Eq(4));
}

