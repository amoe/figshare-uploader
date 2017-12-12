#include <gmock/gmock.h>
#include "xlsx.hh"

using ::testing::Eq;


TEST(XlsxReaderTest, CanGetSheetCount) {
    XlsxReader foo("resources/test.xlsx");

    ASSERT_THAT(foo.getSheetCount(), Eq(1));
    ASSERT_THAT(foo.cellHasValue("A", 2), Eq(true));
    ASSERT_THAT(foo.cellHasValue("A", 7), Eq(false));
    
    foo.rowToString(42);

    // slurp resources/testfile1.xslx

    // you can load from multiple things so we would have the ability to slurp
    // and then load

    // it loads from a std::istream
}
