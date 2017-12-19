#ifndef INTERFACES_HH
#define INTERFACES_HH

#include <string>

class View {
public:
    virtual std::string getSelectedFile() = 0;
    virtual std::string getToken() = 0;
    virtual void reportError(std::string errorText) = 0;
    virtual void addLog(std::string logText) = 0;
    virtual void showFileDialog() = 0;
    virtual void setToken(std::string newToken) = 0;
};

class Presenter {
public:
    virtual void startUpload() = 0;
    virtual void uploadFinished(std::string value) = 0;
    virtual void setView(View* view) = 0;
    virtual void fatalError(std::string what) = 0;
    virtual void pickFile() = 0;
    virtual void initializeView() = 0;
};

#endif // INTERFACES_HH
