#ifndef CONVERTER_REGISTRY_HH
#define CONVERTER_REGISTRY_HH

#include <map>
#include <unordered_map>
#include <QJsonValue>
#include "mapping_types.hh"
#include "enum_class_hash.hh"

using std::map;
using std::unordered_map;

class Converter {
public:
    virtual ~Converter() { }
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


enum class LookupType { 
    DEFINED_TYPE, CATEGORY, GROUP
};
static const unordered_map<string, LookupType> LOOKUP_TYPE_NAMES = {
    {"definedType", LookupType::DEFINED_TYPE},
    {"category", LookupType::CATEGORY},
    {"group", LookupType::GROUP}
};

class LookupRegistry {
public:
    virtual ~LookupRegistry() { }
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
class LookupValueConverter: public Converter {
public:
    LookupValueConverter(LookupRegistry* registry): registry(registry) { }
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);

private:
    LookupRegistry* registry;
};

class LookupListConverter: public Converter {
public:
    LookupListConverter(LookupRegistry* registry): registry(registry) { }
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);

private:
    LookupRegistry* registry;
};


class DiscardConverter: public Converter {
public:
    DiscardConverter() { }
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);
};

class ListOfStringConverter: public Converter {
public:
    ListOfStringConverter() { }
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);
};

class ListOfObjectConverter: public Converter {
public:
    ListOfObjectConverter() { }
    IntermediateMappingOutput applyConversion(string input, OptionsMap options);
};

class ConverterRegistry {
public:
    ConverterRegistry(LookupRegistry* lookups);
    ~ConverterRegistry();

    // This should really be static, but we don't know any sensible way to
    // access state in this case.
    IntermediateMappingOutput convert(ConverterName c, string value, OptionsMap options);
    const vector<ConverterName> getRegisteredConverters() const;

private:
    // It's important that this is an ordered std::map, because 
    // ConverterListModel exploits this property to make sure that field encoders
    // get executed correctly.
    map<ConverterName, Converter*> converterMap;
};

#endif /* CONVERTER_REGISTRY_HH */
