#include <QObject>
#include <QThread>
#include <QString>
#include "slot_adapter.hh"
#include "driver_thread.hh"

class RunUploadTask : public QObject {
public:
    RunUploadTask(
        Driver* driver, StringAdapter adapter, StringAdapter errorAdapter, 
        string inputPath
    );
    ~RunUploadTask();
    void run();

public slots:
    void onPartiallyDone(QString qValue);
    void onFatalError(QString qValue);
    void onFullyDone();

private:
    StringAdapter adapter;
    StringAdapter errorAdapter;
    DriverThread* theTask;
};
