#include <QThread>
#include <QObject>

class ExpensiveOperation : public QThread {
    Q_OBJECT

public:
    ExpensiveOperation(QObject* parent) : QThread(parent) { }
    
    void run() override {
        sleep(10);
        emit resultReady(42);
    }

signals:
    void resultReady(const int& result);
};

