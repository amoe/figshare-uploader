#ifndef CONVERTER_REGISTRY_HH
#define CONVERTER_REGISTRY_HH

#include <QJsonValue>
#include "mapping_types.hh"

class ConverterRegistry {
public:
    ConverterRegistry();
    static QJsonValue convert(Converter c, OptionsMap options);

//private:
//    unordered_map<ConverterName, Converter>
};

#endif /* CONVERTER_REGISTRY_HH */
