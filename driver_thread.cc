#include "logging.hh"
#include "driver_thread.hh"

void DriverThread::run() {
    debugf("thread: sleep 1");
    sleep(3);
    emit partiallyDone(QString("foo"));
    debugf("thread: sleep 2");
    sleep(3);
    debugf("emitting fully done signal");       
    emit fullyDone(42);
}
