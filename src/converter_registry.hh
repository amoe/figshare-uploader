#ifndef CONVERTER_REGISTRY_HH
#define CONVERTER_REGISTRY_HH

#include <unordered_map>
#include <QJsonValue>
#include "converters.hh"
#include "mapping_types.hh"

using std::unordered_map;

class ConverterRegistry {
public:
    ConverterRegistry();
    static QJsonValue convert(ConverterName c, OptionsMap options);

private:
    unordered_map<ConverterName, Converter*> converterMap;
};

#endif /* CONVERTER_REGISTRY_HH */
