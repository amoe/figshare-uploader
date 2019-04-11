#ifndef CONVERTER_REGISTRY_HH
#define CONVERTER_REGISTRY_HH

#include <unordered_map>
#include <QJsonValue>
#include "mapping_types.hh"

using std::unordered_map;

class Converter {
public:
    virtual IntermediateMappingOutput applyConversion(string input, OptionsMap options) = 0;
};

class StringConverter: public Converter {
public:
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);
};

class ConverterRegistry {
public:
    ConverterRegistry();
    ~ConverterRegistry();

    // This should really be static, but we don't know any sensible way to
    // access state in this case.
    IntermediateMappingOutput convert(ConverterName c, string value, OptionsMap options);

private:
    unordered_map<ConverterName, Converter*> converterMap;
};

#endif /* CONVERTER_REGISTRY_HH */
