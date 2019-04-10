#ifndef CONVERTER_REGISTRY_HH
#define CONVERTER_REGISTRY_HH

#include <QJsonValue>
#include "mapping_types.hh"

class ConverterRegistry {
public:
    static QJsonValue convert(Converter c, OptionsMap options);
};

#endif /* CONVERTER_REGISTRY_HH */
