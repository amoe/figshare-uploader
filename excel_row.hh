#ifndef EXCEL_ROW_HH
#define EXCEL_ROW_HH

struct ExcelRow {
public:
    ExcelRow(vector<string> rowData) : rowData(rowData) {}

    vector<string> rowData;
};


#endif // EXCEL_ROW_HH
