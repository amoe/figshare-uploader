#ifndef INTERFACES_HH
#define INTERFACES_HH

class View {
public:
    virtual std::string getSelectedFile() const = 0;
};

class Presenter {
public:
    virtual void someSlot() = 0;
    virtual void uploadFinished() = 0;
};

#endif // INTERFACES_HH
