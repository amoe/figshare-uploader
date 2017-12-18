#include <string>
#include <QString>
#include <QDebug>
#include "logging.hh"
#include "run_upload_task.hh"

using std::string;

RunUploadTask::RunUploadTask(
    Driver* driver, StringAdapter adapter, StringAdapter errorAdapter, string inputPath
) : adapter(adapter), errorAdapter(errorAdapter) {
    theTask = new DriverThread(0, driver, inputPath);   // XXX should pass top level widget

    connect(
        theTask,
        &DriverThread::fullyDone,
        this,
        &RunUploadTask::onFullyDone
    );

    connect(
        theTask,
        &DriverThread::partiallyDone,
        this,
        &RunUploadTask::onPartiallyDone
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
    debugf("calling start on thread object");
    theTask->start();
}

void RunUploadTask::onFullyDone() {
    debugf("inside result ready");
    string greeting = "hello, world";

    adapter(greeting);
}

void RunUploadTask::onPartiallyDone(QString qValue) {
    debugf("inside partially done");
    qDebug() << "value from thread was" << qValue;

    string greeting = "hello, world";

    adapter(greeting);
}
