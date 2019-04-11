#include <QJsonObject>
#include <QString>
#include <iostream>
#include "converter_registry.hh"

IntermediateMappingOutput StringConverter::applyConversion(string input, OptionsMap options) {
    QJsonValue producedValue(QString::fromStdString(input));
    vector<string> producedPaths;
    
    IntermediateMappingOutput result(producedValue, producedPaths, CombinationOperation::CONJOIN);
    return result;
}


ConverterRegistry::ConverterRegistry() {
    std::cout << "initializing converter registry" << std::endl;
    converterMap.insert({ConverterName::STRING, new StringConverter});
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
