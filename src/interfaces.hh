#ifndef INTERFACES_HH
#define INTERFACES_HH

#include <string>
#include "progress_reporter.hh"

class View {
public:
    virtual std::string getSelectedFile() = 0;
    virtual std::string getToken() = 0;
    virtual void reportError(std::string errorText) = 0;
    virtual void addLog(std::string logText) = 0;
    virtual void showFileDialog() = 0;
    virtual void setToken(std::string newToken) = 0;
    virtual void setProgressReporter(ViewProgressAdapter* reporter) = 0;
    virtual void showAboutDialog() = 0;
 };

class Presenter {
public:
    virtual void startUpload() = 0;
    virtual void uploadFinished(std::string value) = 0;
    virtual void setView(View* view) = 0;
    virtual void fatalError(std::string what) = 0;
    virtual void pickFile() = 0;
    virtual void initializeView() = 0;
    virtual void showAboutDialog() = 0;
    virtual void showSettingsDialog() = 0;
};

#endif // INTERFACES_HH
