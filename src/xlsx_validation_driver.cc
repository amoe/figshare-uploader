#include <iostream>
#include "xlsx.hh"

using std::cerr;
using std::endl;

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Please pass the path to one XLSX file on the command line." << endl;
        return 1;
    }

    // If something goes wrong with the file, the following code will throw.

    XlsxReader theReader(argv[1]);
    int rowCount = theReader.getRowCount();
    for (int i = 0; i <= rowCount; i++) {
        vector<string> rowData = theReader.rowToString(i);
    }

    return 0;
}
