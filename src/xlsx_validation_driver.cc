#include <iostream>
#include "xlsx.hh"

int main(int argc, char** argv) {
    XlsxReader theReader(argv[1]);

    int rowCount = theReader.getRowCount();
    for (int i = 0; i <= rowCount; i++) {
        vector<string> rowData = theReader.rowToString(i);
    }

    return 0;
}
