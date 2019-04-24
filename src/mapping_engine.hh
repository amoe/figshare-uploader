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
    virtual ~MappingEngine() { }
    virtual MappingOutput convert(vector<string> document, MappingScheme scheme) const = 0;
};

class MappingEngineImpl: public MappingEngine {
public:
    MappingEngineImpl(ConverterRegistry* converterRegistry):
        converterRegistry(converterRegistry) { }
    ~MappingEngineImpl() { }

    MappingOutput convert(vector<string> document, MappingScheme scheme) const;

private:
    ConverterRegistry* converterRegistry;
};

#endif /* MAPPING_ENGINE_HH */
