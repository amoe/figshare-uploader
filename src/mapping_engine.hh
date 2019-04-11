#ifndef MAPPING_ENGINE_HH
#define MAPPING_ENGINE_HH

#include <vector>
#include <string>
#include <QJsonObject>
#include "converter_registry.hh"
#include "mapping_types.hh"

class MappingEngine {
public:
    MappingEngine() { }
    MappingOutput convert(vector<string> document, MappingScheme scheme);

private:
    ConverterRegistry converterRegistry;
};

#endif /* MAPPING_ENGINE_HH */
