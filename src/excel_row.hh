#ifndef EXCEL_ROW_HH
#define EXCEL_ROW_HH

struct ExcelRow {
public:
    ExcelRow(vector<string> rowData, int rowNumber) : rowData(rowData), rowNumber(rowNumber) {}

    int rowNumber;
    vector<string> rowData;
};


#endif // EXCEL_ROW_HH
