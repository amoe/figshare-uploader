#ifndef PROGRESS_REPORTER_HH
#define PROGRESS_REPORTER_HH

#include "interfaces.hh"

class ProgressReporter {
public:
    virtual void updateProgress(std::string logText) = 0;
};

class ViewProgressAdapter : public ProgressReporter {
public:
    ViewProgressAdapter(View* view) : view(view) { };
    void updateProgress(std::string logText);

private:
    View* view;
};


class NullProgressReporter : public ProgressReporter {
public:
    void updateProgress(std::string logText) {
        // Do absolutely nothing
    }
};

#endif // PROGRESS_REPORTER_HH
