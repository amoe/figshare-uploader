#include <string>
#include "progress_reporter.hh"

using std::string;

void ViewProgressAdapter::updateProgress(string logText) {
    // Just delegate to the view
    view->addLog(logText);
}
