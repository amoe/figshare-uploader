#include <gmock/gmock.h>
#include <xlnt/xlnt.hpp>

using ::testing::Eq;

class XlsxReader {
public:
    XlsxReader(const std::string path) {
        wb.load(path);
    }

    std::size_t getSheetCount() {
        return wb.sheet_count();
    }
    
private:
    xlnt::workbook wb;
};

TEST(XlsxReaderTest, CanGetSheetCount) {
    XlsxReader foo("resources/test.xlsx");

    ASSERT_THAT(foo.getSheetCount(), Eq(1));

    // slurp resources/testfile1.xslx

    // you can load from multiple things so we would have the ability to slurp
    // and then load

    // it loads from a std::istream
}
