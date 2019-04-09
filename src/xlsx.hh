#include <vector>
#include <string>
#include <xlnt/xlnt.hpp>

using std::string;
using std::ostringstream;
using std::vector;
using RowContainer = vector<string>;

class XlsxReader {
public:
    XlsxReader(const std::string path);

    std::size_t getSheetCount();
    bool cellHasValue(string column, int row);
    RowContainer rowToString(int row);
    int getRowCount();

private:
    xlnt::workbook wb;
};
