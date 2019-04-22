#ifndef EXCEL_ROW_HH
#define EXCEL_ROW_HH

struct ExcelRow {
public:
    ExcelRow(vector<string> rowData, int rowNumber) : rowData(rowData), rowNumber(rowNumber) {}

    vector<string> rowData;
    int rowNumber;
};


#endif // EXCEL_ROW_HH
