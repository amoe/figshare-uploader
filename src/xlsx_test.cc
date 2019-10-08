#include <gmock/gmock.h>
#include "column_mapping.hh"
#include "xlsx.hh"
#include "test_vocabulary.hh"

using std::vector;
using std::string;

TEST(XlsxReaderTest, CanGetSheetCount) {
    XlsxReader foo("resources/test.xlsx");

    ASSERT_THAT(foo.getSheetCount(), Eq(1));
    ASSERT_THAT(foo.cellHasValue("A", 2), Eq(true));
    ASSERT_THAT(foo.cellHasValue("A", 20), Eq(false));
    
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



TEST(XlsxReaderTest, DateFormattedFieldCanBeTransformedCorrectlyToString) {
    XlsxReader foo("resources/test.xlsx");
    vector<string> result = foo.rowToString(7);

    ASSERT_THAT(result.at(column_mapping::DATE), "2018-12-23");
}


