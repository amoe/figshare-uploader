#ifndef INTERFACES_HH
#define INTERFACES_HH

#include <string>

using std::string;

class View {
public:
    virtual string getSelectedFile() = 0;
    virtual void reportError(std::string errorText) = 0;
    virtual void addLog(std::string logText) = 0;
};

class Presenter {
public:
    virtual void startUpload() = 0;
    virtual void uploadFinished(string value) = 0;
    virtual void setView(View* view) = 0;
    virtual void fatalError(string what) = 0;
};

#endif // INTERFACES_HH
