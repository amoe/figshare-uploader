#include <QObject>
#include <QThread>
#include <QString>
#include "slot_adapter.hh"
#include "expensive_operation.hh"

class RunUploadTask : public QObject {
public:
    RunUploadTask(SlotAdapter adapter);
    ~RunUploadTask();
    void run();

public slots:
    void onPartiallyDone(QString value);
    void onFullyDone();

private:
    SlotAdapter adapter;
    ExpensiveOperation* theTask;
};
