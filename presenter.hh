#ifndef PRESENTER_HH
#define PRESENTER_HH

#include "driver.hh"
#include "interfaces.hh"

class PresenterImpl : public Presenter {
public:
    PresenterImpl(Driver* driver) : driver(driver) {
        this->view = NULL;
    }

    void startUpload();
    void uploadFinished(string value);
    void setView(View* view);
    void fatalError(string what);
    void pickFile();

private:
    View* view;
    Driver* driver;
};

#endif
