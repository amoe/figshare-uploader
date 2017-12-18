#include "logging.hh"
#include "expensive_operation.hh"

void ExpensiveOperation::run() {
    debugf("thread: sleep 1");
    sleep(3);
    emit partiallyDone(42);
    debugf("thread: sleep 2");
    sleep(3);
    debugf("emitting fully done signal");       
    emit fullyDone(42);
}
