#include <QJsonObject>
#include <iostream>
#include "converter_registry.hh"

ConverterRegistry::ConverterRegistry() {
    std::cout << "initializing converter registry" << std::endl;
}

QJsonValue ConverterRegistry::convert(ConverterName c, OptionsMap options) {
    QJsonObject empty;
    return empty;
}
