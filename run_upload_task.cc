#include "logging.hh"
#include "run_upload_task.hh"
#include "expensive_operation.hh"

RunUploadTask::RunUploadTask(SlotAdapter adapter)  : adapter(adapter) {
    theTask = new ExpensiveOperation(0);
}

RunUploadTask::~RunUploadTask() {
    delete theTask;
}

void RunUploadTask::run() {
    debugf("doing nothing");
}
