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
    // sleep(10);
    
    XlsxReader theReader(inputPath);

    for (int i = 2; i <= 6; i++) {
        debugf("handling row %d", i);
        vector<string> rowData = theReader.rowToString(i);
        ExcelRow row(rowData);
        driver->handleRow(row);
    }

    // debugf("thread: sleep 1");
    // sleep(3);

    // // Note that we have to emit a QString here because std::string isn't
    // // handled by the signal / slot mechanism.

    // emit partiallyDone(QString("foo"));

    // debugf("thread: sleep 2");
    // sleep(3);
    // debugf("emitting fully done signal");       
    // emit fullyDone(42);
}



