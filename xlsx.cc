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

    bool cellHasValue(std::string column, int row) {
        xlnt::worksheet ws = wb.active_sheet();
        auto cell = ws.cell(column, row);
        return cell.has_value();
    }

    std::vector<std::string> rowToString(int row) {
        xlnt::worksheet ws = wb.active_sheet();
        
        std::vector<std::string> result;

        // select one and just one row
        xlnt::range range = ws.range("A2:U2");

        // this is equivalent to `strict-first`
        xlnt::cell_vector cv = range.front();


        for (auto cell : cv) {
            auto strVersion = cell.to_string();
            std::cout << strVersion;
            result.push_back(strVersion);
        }

        return result;
    }
    
private:
    xlnt::workbook wb;
};

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
