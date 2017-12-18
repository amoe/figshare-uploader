#include "logging.hh"
#include "run_upload_task.hh"
#include "expensive_operation.hh"

RunUploadTask::RunUploadTask(SlotAdapter adapter)  : adapter(adapter) {
    theTask = new ExpensiveOperation(0);

    connect(
        theTask,
        &ExpensiveOperation::resultReady,
        this,
        &RunUploadTask::onResultReady
    );
}

RunUploadTask::~RunUploadTask() {
    delete theTask;
}

void RunUploadTask::run() {
    debugf("calling start on thread object");
    theTask->start();
}

void RunUploadTask::onResultReady() {
    debugf("inside result ready");
    adapter();
}
