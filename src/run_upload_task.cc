#include <string>
#include <QString>
#include <QDebug>
#include "logging.hh"
#include "run_upload_task.hh"

using std::string;

RunUploadTask::RunUploadTask(
    Driver* driver, StringAdapter adapter, StringAdapter errorAdapter,
    string inputPath, const MappingScheme& fieldMappings
) : adapter(adapter), errorAdapter(errorAdapter) {
    theTask = new DriverThread(0, driver, inputPath, fieldMappings);   // XXX should pass top level widget?

    connect(
        theTask,
        &DriverThread::fullyDone,
        this,
        &RunUploadTask::onFullyDone
    );

    connect(
        theTask,
        &DriverThread::fatalError,
        this,
        &RunUploadTask::onFatalError
    );
}

void RunUploadTask::onFatalError(QString what) {
    errorAdapter(what.toStdString());
}

RunUploadTask::~RunUploadTask() {
    delete theTask;
}

void RunUploadTask::run() {
    spdlog::info("calling start on thread object");
    theTask->start();
}

void RunUploadTask::onFullyDone() {
    spdlog::info("inside result ready");
    string greeting = "hello, world";
    adapter(greeting);
}
