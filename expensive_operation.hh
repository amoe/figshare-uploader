#ifndef EXPENSIVE_OPERATION_HH
#define EXPENSIVE_OPERATION_HH

#include <QThread>
#include <QObject>
#include <QString>

using std::string;

class ExpensiveOperation : public QThread {
    Q_OBJECT

public:
    ExpensiveOperation(QObject* parent) : QThread(parent) { }
    void run() override;

signals:
    void partiallyDone(QString result);
    void fullyDone(const int& result);
};


#endif // EXPENSIVE_OPERATION_HH
