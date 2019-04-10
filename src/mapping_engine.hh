#ifndef MAPPING_ENGINE_HH
#define MAPPING_ENGINE_HH

#include <vector>
#include <string>
#include <QJsonObject>
#include "mapping_types.hh"
#include "mapping_outputs.hh"

class MappingEngine {
public:
    MappingOutput convert(vector<string> document, MappingScheme scheme);
};

#endif /* MAPPING_ENGINE_HH */
