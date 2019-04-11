#ifndef CONVERTERS_HH
#define CONVERTERS_HH

#include <QJsonValue>
#include "mapping_types.hh"

// It's not totally clear if this should be something that returns values.
// Instead it should probably modify the passed in value, as a sort of reduction.
// That would mean that validation rules would all have to be applied first.
// But we also have to take into account how we are going to implement 
// ContributeFilesConverter.
class Converter {
public:
    virtual void applyConversion(QJsonValue seed, string input, OptionsMap options) = 0;
};

class StringConverter: public Converter {
public:
    void applyConversion(QJsonValue seed, string input, OptionsMap options);
};

#endif /* CONVERTERS_HH */
