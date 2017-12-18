#include "logging.hh"
#include "run_upload_task.hh"
#include "expensive_operation.hh"

RunUploadTask::RunUploadTask(SlotAdapter adapter)  : adapter(adapter) {
    theTask = new ExpensiveOperation(0);

    connect(
        theTask,
        &ExpensiveOperation::fullyDone,
        this,
        &RunUploadTask::onFullyDone
    );

    connect(
        theTask,
        &ExpensiveOperation::partiallyDone,
        this,
        &RunUploadTask::onPartiallyDone
    );

}

RunUploadTask::~RunUploadTask() {
    delete theTask;
}

void RunUploadTask::run() {
    debugf("calling start on thread object");
    theTask->start();
}

void RunUploadTask::onFullyDone() {
    debugf("inside result ready");
    adapter();
}

void RunUploadTask::onPartiallyDone() {
    debugf("inside partially done");
    adapter();
}
