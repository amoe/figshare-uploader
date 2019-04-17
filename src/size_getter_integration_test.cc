#include <gmock/gmock.h>
#include "size_getter.hh"
#include "test_utility.hh"
#include "stubs.hh"
#include "requests.hh"
#include "file_spec_generator.hh"
#include "test_vocabulary.hh"

using std::string;

TEST(SizeGetterTest, CanGetSize) {
    SizeGetter* getter = new QtSizeGetter;
    int64_t result = getter->getSize("resources/test.xlsx");
    ASSERT_THAT(result, Eq(9413));
}

