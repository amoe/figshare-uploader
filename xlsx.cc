#include <gmock/gmock.h>
#include <xlnt/xlnt.hpp>
#include "xlsx.hh"

using ::testing::Eq;

XlsxReader::XlsxReader(const std::string path) {
    wb.load(path);
}

std::size_t XlsxReader::getSheetCount() {
    return wb.sheet_count();
}

bool XlsxReader::cellHasValue(std::string column, int row) {
    xlnt::worksheet ws = wb.active_sheet();
    auto cell = ws.cell(column, row);
    return cell.has_value();
}

std::vector<std::string> XlsxReader::rowToString(int row) {
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
    
