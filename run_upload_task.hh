#include <QObject>
#include <QThread>
#include "slot_adapter.hh"

class RunUploadTask : public QObject {
public:
    RunUploadTask(SlotAdapter adapter);
    ~RunUploadTask();
    void run();

private:
    SlotAdapter adapter;
    QThread* theTask;
};
