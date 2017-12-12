#include <xlnt/xlnt.hpp>

class XlsxReader {
public:
    XlsxReader(const std::string path);

    std::size_t getSheetCount();

    bool cellHasValue(std::string column, int row);

    std::vector<std::string> rowToString(int row);
    
private:
    xlnt::workbook wb;
};
