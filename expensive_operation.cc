#include "logging.hh"
#include "expensive_operation.hh"

void ExpensiveOperation::run() {
    debugf("about to sleep inside thread");
    sleep(3);
    debugf("slept inside thread, about to emit signal");       
    emit resultReady(42);
}
