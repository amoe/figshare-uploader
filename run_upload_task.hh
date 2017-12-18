#include <QObject>
#include <QThread>
#include "slot_adapter.hh"
#include "expensive_operation.hh"

class RunUploadTask : public QObject {
public:
    RunUploadTask(SlotAdapter adapter);
    ~RunUploadTask();
    void run();

public slots:
    void onPartiallyDone();
    void onFullyDone();

private:
    SlotAdapter adapter;
    ExpensiveOperation* theTask;
};
