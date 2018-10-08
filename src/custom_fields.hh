#ifndef CUSTOM_FIELDS_HH
#define CUSTOM_FIELDS_HH

#include <QJsonObject>

// The CustomFieldSet has to be copy-safe.  That means we can't use polymorphism
// to implement the encoding behaviour.
class CustomFieldSet {
public:
    CustomFieldSet() { }

    void add();
    QJsonObject render() const;
};

#endif /* CUSTOM_FIELDS_HH */
