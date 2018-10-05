#include <sstream>
#include <gmock/gmock.h>
#include <xlnt/xlnt.hpp>
#include "xlsx.hh"
#include "column_mapping.hh"

using ::testing::Eq;
using std::string;
using std::ostringstream;

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

// This isn't the same as max_row() or highest_row(), because it makes sure
// that blank rows don't arbitrarily fill up the test sheet, as happened in the
// demo data.
int XlsxReader::getRowCount() {
    xlnt::worksheet ws = wb.active_sheet();
    const auto rows = ws.rows();

    // reverse iteration, I found this pattern in the xlnt unit tests
    for (auto ws_iter = rows.rbegin(); ws_iter != rows.rend(); ws_iter++) {
        const auto row = *ws_iter;

        for (auto row_iter = row.rbegin(); row_iter != row.rend(); row_iter++) {
            const auto cell = *row_iter;

            if (cell.has_value()) {
                return cell.row();
            }
        }
    }

    // if we got here, the sheet is completely empty anyway
    return 0;
}

std::vector<std::string> XlsxReader::rowToString(int row) {
    xlnt::worksheet ws = wb.active_sheet();
        
    std::vector<std::string> result;

    // this should be done better somehow
    ostringstream rangeSpec;
    rangeSpec << column_mapping::MINIMUM_COLUMN
              << row << ":" << column_mapping::MAXIMUM_COLUMN << row;

    // select one and just one row
    xlnt::range range = ws.range(rangeSpec.str());

    // this is equivalent to `strict-first`
    xlnt::cell_vector cv = range.front();

    for (auto cell : cv) {
        auto strVersion = cell.to_string();
        result.push_back(strVersion);
    }

    return result;
}
    
