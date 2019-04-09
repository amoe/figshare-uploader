#include <gmock/gmock.h>

using ::testing::Test;
using ::testing::Eq;

class MappingEngineTest: public Test {

public:
    MappingEngineTest() { }
};


TEST_F(MappingEngineTest, SanityCheck) {
    ASSERT_THAT(2 + 2, Eq(4));
}

