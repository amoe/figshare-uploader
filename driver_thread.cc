#include "logging.hh"
#include "driver_thread.hh"
#include "driver.hh"
#include "xlsx.hh"

void DriverThread::run() {
    try {
        perform();
    } catch (std::runtime_error e) {
        debugf("caught std-exception in driver thread handler: %s", e.what());
        emit fatalError(QString(e.what()));
    } catch (std::exception e) {
        debugf("caught runtime-exception in driver thread handler: %s", e.what());
        emit fatalError(QString(e.what()));
    }
}


void DriverThread::perform() {
    XlsxReader theReader(inputPath);
    
    int rowCount = theReader.getRowCount();
    debugf("detected row count: %d", theReader.getRowCount());

    for (int i = 2; i <= rowCount; i++) {
        debugf("handling row %d", i);
        vector<string> rowData = theReader.rowToString(i);
        ExcelRow row(rowData);
        driver->handleRow(row);
    }

    emit fullyDone(42);
}



