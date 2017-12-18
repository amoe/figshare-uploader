#ifndef DRIVER_THREAD_HH
#define DRIVER_THREAD_HH

#include <QThread>
#include <QObject>
#include <QString>
#include "driver.hh"

using std::string;

class DriverThread : public QThread {
    Q_OBJECT

public:
    DriverThread(QObject* parent, Driver* driver) : QThread(parent) { }
    void run() override;

signals:
    void partiallyDone(QString result);
    void fullyDone(const int& result);

private:
    Driver* driver;
};


#endif // DRIVER_THREAD_HH
