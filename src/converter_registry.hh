#ifndef CONVERTER_REGISTRY_HH
#define CONVERTER_REGISTRY_HH

#include <unordered_map>
#include <QJsonValue>
#include "mapping_types.hh"

using std::unordered_map;

// This is basically a hack to allow storing enum classes in an unordered_map,
// and it should definitely be moved somewhere more useful.

struct EnumClassHash {
    template <typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};


class Converter {
public:
    virtual IntermediateMappingOutput applyConversion(string input, OptionsMap options) = 0;
};

class StringConverter: public Converter {
public:
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);
};

class ContributeFilesConverter: public Converter {
public:
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);
};


enum class LookupType { DEFINED_TYPE };
static const unordered_map<string, LookupType> LOOKUP_TYPE_NAMES = {
    {"definedType", LookupType::DEFINED_TYPE}
};

class LookupRegistry {
public:
    virtual QJsonValue lookupByString(LookupType type, string value) = 0;
};

class LookupRegistryImpl: public LookupRegistry {
public:
    LookupRegistryImpl();
    ~LookupRegistryImpl();
    QJsonValue lookupByString(LookupType type, string value);

private:
    unordered_map<string, string> definedTypeMap;
};

// This one works using a similar pattern.  The registry can be passed in for
// stubbing.
class LookupListConverter: public Converter {
public:
    LookupListConverter(LookupRegistry* registry): registry(registry) { }
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);

private:
    LookupRegistry* registry;
};

class ConverterRegistry {
public:
    ConverterRegistry(LookupRegistry* lookups);
    ~ConverterRegistry();

    // This should really be static, but we don't know any sensible way to
    // access state in this case.
    IntermediateMappingOutput convert(ConverterName c, string value, OptionsMap options);

private:
    unordered_map<ConverterName, Converter*, EnumClassHash> converterMap;
};

#endif /* CONVERTER_REGISTRY_HH */
