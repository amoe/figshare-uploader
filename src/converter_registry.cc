#include <QJsonObject>
#include <iostream>
#include "converter_registry.hh"
#include "converters.hh"

ConverterRegistry::ConverterRegistry() {
    std::cout << "initializing converter registry" << std::endl;
    converterMap.insert({ConverterName::STRING, new StringConverter});
}


// There becomes an extremely scoping problem here.
// It's clear that we can't just 
QJsonValue ConverterRegistry::convert(ConverterName c, OptionsMap options) {
    QJsonObject empty;
//    Converter* converter = converterMap.at(c);
    return empty;
}
