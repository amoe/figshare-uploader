#include <QJsonObject>
#include <QString>
#include <iostream>
#include "converter_registry.hh"
#include "utility.hh"

QJsonValue LookupRegistryImpl::lookupByString(LookupType type, string value) {
    QJsonValue result;
    return result;
}


IntermediateMappingOutput StringConverter::applyConversion(string input, OptionsMap options) {
    QJsonValue producedValue(QString::fromStdString(input));
    vector<string> producedPaths;
    
    IntermediateMappingOutput result(producedValue, producedPaths, CombinationOperation::CONJOIN);
    return result;
}

IntermediateMappingOutput ContributeFilesConverter::applyConversion(string input, OptionsMap options) {
    QJsonValue producedValue;    // Will be initialized to null.
    string delimiterRegex = options.at("delimiter").value();
    vector<string> producedPaths = splitByRegexp(input, delimiterRegex);
    IntermediateMappingOutput result(producedValue, producedPaths, CombinationOperation::CONJOIN);
    return result;
}



IntermediateMappingOutput LookupListConverter::applyConversion(string input, OptionsMap options) {
    string resourceName = options.at("resourceName").value();
    LookupType type = LOOKUP_TYPE_NAMES.at(resourceName);
    QJsonValue producedValue = registry->lookupByString(type, input);
    vector<string> producedPaths;

    IntermediateMappingOutput result(producedValue, producedPaths, CombinationOperation::CONJOIN);
    return result;
}


ConverterRegistry::ConverterRegistry(LookupRegistry* lookupRegistry) {
    std::cout << "initializing converter registry" << std::endl;
    converterMap.insert({ConverterName::STRING, new StringConverter});
    converterMap.insert({ConverterName::CONTRIBUTE_FILES, new ContributeFilesConverter});

    // Lookup list needs more information to initialize itself.
    converterMap.insert({ConverterName::LOOKUP_LIST, new LookupListConverter(lookupRegistry)});
}

ConverterRegistry::~ConverterRegistry() {
    std::cout << "destroying converter registry" << std::endl;
    for (const auto& pair: converterMap) {
        Converter* c = pair.second;
        delete c;
    }
    std::cout << "successfully deleted everything" << std::endl;
}


// We are a simple delegator.
IntermediateMappingOutput ConverterRegistry::convert(ConverterName c, string value, OptionsMap options) {
    Converter* converter = converterMap.at(c);
    return converter->applyConversion(value, options);
}
