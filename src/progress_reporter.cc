#include <string>
#include <QString>
#include "progress_reporter.hh"

using std::string;

void ViewProgressAdapter::updateProgress(string logText) {
    emit progressReport(QString::fromStdString(logText));
}
