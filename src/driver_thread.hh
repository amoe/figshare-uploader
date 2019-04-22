#ifndef DRIVER_THREAD_HH
#define DRIVER_THREAD_HH

#include <QThread>
#include <QObject>
#include <QString>
#include "driver.hh"
#include "mapping_types.hh"

using std::string;

class DriverThread : public QThread {
    Q_OBJECT

public:
    DriverThread(
        QObject* parent, Driver* driver, string inputPath, 
        const MappingScheme& fieldMappings
    ) : QThread(parent),
        driver(driver), inputPath(inputPath), fieldMappings(fieldMappings) { }
    void run() override;

signals:
    void fullyDone(const int& result);
    void fatalError(QString what);

private:
    Driver* driver;
    string inputPath;
    const MappingScheme& fieldMappings;

    void perform();
};


#endif // DRIVER_THREAD_HH
