#ifndef PRESENTER_HH
#define PRESENTER_HH

#include "driver.hh"
#include "interfaces.hh"

class PresenterImpl : public Presenter {
public:
    PresenterImpl(Driver* driver) : driver(driver) {
        this->view = NULL;
    }

    void someSlot();
    void uploadFinished(string value);
    void setView(View* view);

private:
    View* view;
    Driver* driver;
};

#endif
