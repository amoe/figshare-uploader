#include <gmock/gmock.h>
#include "size_getter.hh"

using ::testing::Eq;

TEST(SizeGetterTest, CanGetSize) {
    SizeGetter* getter = new QtSizeGetter;
    int64_t result = getter->getSize("resources/test.xlsx");
    ASSERT_THAT(result, Eq(29907));
}

