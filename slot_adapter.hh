#ifndef SLOT_ADAPTER_HH
#define SLOT_ADAPTER_HH

#include "interfaces.hh"

// This is the long way round of writing a lambda expression.  Note the double
// parens to overload application.

typedef void (Presenter::*PresenterSlot)(); //MyTypedef is a type!

class SlotAdapter {
public:
    SlotAdapter(Presenter* p, PresenterSlot f) : p(p), f(f) { }

    void operator()() const {
        // Call member function through the provided function pointer
        (p->*f)();
    }

    Presenter* p;
    PresenterSlot f;
};

#endif // SLOT_ADAPTER_HH
