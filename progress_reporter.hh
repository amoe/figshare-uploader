#ifndef PROGRESS_REPORTER_HH
#define PROGRESS_REPORTER_HH

#include <QObject>

class ProgressReporter {
public:
    virtual void updateProgress(std::string logText) = 0;
};

class ViewProgressAdapter :  public QObject, public ProgressReporter {
    Q_OBJECT

public:
    void updateProgress(std::string logText);

signals:
    void progressReport(QString logText);
};


class NullProgressReporter : public ProgressReporter {
public:
    void updateProgress(std::string logText) {
        // Do absolutely nothing
    }
};

#endif // PROGRESS_REPORTER_HH
