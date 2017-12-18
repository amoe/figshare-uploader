#include "expensive_operation.hh"

void ExpensiveOperation::run() {
    sleep(10);
    emit resultReady(42);
}
