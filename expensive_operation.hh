#include <QThread>
#include <QObject>

class ExpensiveOperation : public QThread {
    Q_OBJECT

public:
    ExpensiveOperation(QObject* parent) : QThread(parent) { }
    void run() override;

signals:
    void resultReady(const int& result);
};

