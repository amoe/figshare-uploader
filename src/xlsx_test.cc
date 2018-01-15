#include <gmock/gmock.h>
#include "xlsx.hh"

using ::testing::Eq;
using ::testing::Ne;

using std::vector;
using std::string;


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

TEST(XlsxReaderTest, CanGetRow) {
    XlsxReader foo("resources/test.xlsx");
    vector<string> result1 = foo.rowToString(2);
    vector<string> result2 = foo.rowToString(3);

    ASSERT_THAT(result1, Ne(result2));
}
