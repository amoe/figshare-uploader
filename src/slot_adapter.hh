#ifndef SLOT_ADAPTER_HH
#define SLOT_ADAPTER_HH

#include <string>
#include "interfaces.hh"

using std::string;

// This is the long way round of writing a lambda expression.  Note the double
// parens to overload application.

// This defines the type alias "PresenterSlot"
typedef void (Presenter::*PresenterSlot)();
typedef void (Presenter::*PresenterStringSlot)(string value);

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

class StringAdapter {
public:
    StringAdapter(Presenter* p, PresenterStringSlot f) : p(p), f(f) { }

    void operator()(string value) const {
        // Call member function through the provided function pointer
        (p->*f)(value);
    }

    Presenter* p;
    PresenterStringSlot f;
};

#endif // SLOT_ADAPTER_HH
