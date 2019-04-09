#ifndef MAPPING_ENGINE_HH
#define MAPPING_ENGINE_HH

#include <vector>
#include <string>
#include <QJsonObject>
#include "mapping_types.hh"

class MappingEngine {
public:
    QJsonObject convert(vector<string> document, MappingScheme scheme);
};

#endif /* MAPPING_ENGINE_HH */
