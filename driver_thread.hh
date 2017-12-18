#ifndef DRIVER_THREAD_HH
#define DRIVER_THREAD_HH

#include <QThread>
#include <QObject>
#include <QString>

using std::string;

class DriverThread : public QThread {
    Q_OBJECT

public:
    DriverThread(QObject* parent) : QThread(parent) { }
    void run() override;

signals:
    void partiallyDone(QString result);
    void fullyDone(const int& result);
};


#endif // DRIVER_THREAD_HH
