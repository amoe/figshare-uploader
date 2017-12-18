#include <QObject>
#include <QThread>
#include <QString>
#include "slot_adapter.hh"
#include "expensive_operation.hh"

class RunUploadTask : public QObject {
public:
    RunUploadTask(StringAdapter adapter);
    ~RunUploadTask();
    void run();

public slots:
    void onPartiallyDone(QString qValue);
    void onFullyDone();

private:
    StringAdapter adapter;
    ExpensiveOperation* theTask;
};
