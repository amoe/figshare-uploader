#ifndef PRESENTER_HH
#define PRESENTER_HH

#include "interfaces.hh"

class PresenterImpl : public Presenter {
public:
    PresenterImpl(View* view) : view(view) { }
    void someSlot();

private:
    View* view;
};

#endif
