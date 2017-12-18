#ifndef INTERFACES_HH
#define INTERFACES_HH

#include <string>

using std::string;

class View {
public:
    virtual string getSelectedFile() const = 0;
};

class Presenter {
public:
    virtual void someSlot() = 0;
    virtual void uploadFinished(string value) = 0;
};

#endif // INTERFACES_HH
