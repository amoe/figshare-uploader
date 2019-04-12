#ifndef MAPPING_ENGINE_HH
#define MAPPING_ENGINE_HH

#include <vector>
#include <string>
#include <QJsonObject>
#include "converter_registry.hh"
#include "mapping_types.hh"

// Lookups are the only parts that can potentially touch external services.
// So we need a way to inject this information.
// The converter registry is really just an implementation detail of the
// engine itself, so doesn't need to be constructor-injected.

class MappingEngine {
public:
    MappingEngine(LookupRegistry* lookupRegistry): lookupRegistry(lookupRegistry) {
        converterRegistry = new ConverterRegistry(lookupRegistry);
    }
    ~MappingEngine() {
        delete converterRegistry;
    }

    MappingOutput convert(vector<string> document, MappingScheme scheme);

private:
    ConverterRegistry* converterRegistry;
    LookupRegistry* lookupRegistry;
};

#endif /* MAPPING_ENGINE_HH */
