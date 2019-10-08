#include <stdexcept>
#include "logging.hh"
#include "driver_thread.hh"
#include "driver.hh"
#include "xlsx.hh"

// Skip one row by default
const int INITIAL_ROW = 2;

void DriverThread::run() {
    try {
        perform();
    } catch (std::runtime_error& e) {
        spdlog::info("caught std-exception in driver thread handler: {}", e.what());
        emit fatalError(QString(e.what()));
    } catch (std::exception& e) {
        spdlog::info("caught runtime-exception in driver thread handler: {}", e.what());
        emit fatalError(QString(e.what()));
    }
}


void DriverThread::perform() {
    XlsxReader theReader(inputPath);
    
    spdlog::info("using input path: {}", inputPath.c_str());

    int rowCount = theReader.getRowCount();
    spdlog::info("detected row count: {}", theReader.getRowCount());

    for (int i = INITIAL_ROW; i <= rowCount; i++) {
        spdlog::info("handling row {}", i);
        vector<string> rowData = theReader.rowToString(i);
        ExcelRow row(rowData, i);
        driver->handleRow(row, inputPath, fieldMappings);
    }

    driver->log("Finished uploading.");

    emit fullyDone(42);
}



