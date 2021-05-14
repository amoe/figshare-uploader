#include <sstream>
#include <xlnt/xlnt.hpp>
#include "xlsx.hh"
#include "column_mapping.hh"

XlsxReader::XlsxReader(const string path) {
    wb.load(path);
}

std::size_t XlsxReader::getSheetCount() {
    return wb.sheet_count();
}

bool XlsxReader::cellHasValue(string column, int row) {
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

// Rows are one-based!
RowContainer XlsxReader::rowToString(int row) {
    xlnt::worksheet ws = wb.active_sheet();
        
    RowContainer result;

    xlnt::column_t highestColumn = ws.highest_column();
    
    // this should be done better somehow
    ostringstream rangeSpec;
    rangeSpec << xlnt::column_t::column_string_from_index(1)
              << row
              << ":"
              << xlnt::column_t::column_string_from_index(highestColumn.index)
              << row;

    
    // select one and just one row
    xlnt::range range = ws.range(rangeSpec.str());

    // this is equivalent to `strict-first`
    xlnt::cell_vector cv = range.front();

    for (auto cell : cv) {
        string strVersion;

        if (cell.is_date()) {
            // By default, date-formatted cells render as a number, days from
            // a base date, which we don't want in this case.
            // 
            // Below bug contains example usage of the number-format system
            // to properly convert to string.
            // https://github.com/tfussell/xlnt/issues/220
            xlnt::number_format nf;
            nf.format_string("YYYY-MM-DD");
            strVersion = nf.format(cell.value<double>(), cell.base_date());
        } else {
            strVersion = cell.to_string();
        }

        result.push_back(strVersion);
    }

    return result;
}
