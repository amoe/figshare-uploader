#include "logging.hh"
#include "driver_thread.hh"
#include "driver.hh"

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
    vector<string> rowData = {
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    };

    ExcelRow row(rowData);

    driver->handleRow(row);

    debugf("thread: sleep 1");
    sleep(3);

    // Note that we have to emit a QString here because std::string isn't
    // handled by the signal / slot mechanism.

    emit partiallyDone(QString("foo"));

    debugf("thread: sleep 2");
    sleep(3);
    debugf("emitting fully done signal");       
    emit fullyDone(42);
}



