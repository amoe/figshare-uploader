#include <stdexcept>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <iostream>
#include "converter_registry.hh"
#include "utility.hh"

ConverterRegistry::ConverterRegistry(LookupRegistry* lookupRegistry) {
    std::cout << "initializing converter registry" << std::endl;
    converterMap.insert({ConverterName::STRING, new StringConverter});
    converterMap.insert({ConverterName::CONTRIBUTE_FILES, new ContributeFilesConverter});

    // Lookup list needs more information to initialize itself.
    converterMap.insert({ConverterName::LOOKUP_LIST, new LookupListConverter(lookupRegistry)});

    converterMap.insert({ConverterName::DISCARD, new DiscardConverter});
    converterMap.insert({ConverterName::LIST_OF_STRING, new ListOfStringConverter});
}

ConverterRegistry::~ConverterRegistry() {
    std::cout << "destroying converter registry" << std::endl;
    for (const auto& pair: converterMap) {
        Converter* c = pair.second;
        delete c;
    }
    std::cout << "successfully deleted everything" << std::endl;
}

const vector<ConverterName> ConverterRegistry::getRegisteredConverters() const {
    vector<ConverterName> result;

    for (const auto& pair: converterMap) {
        result.push_back(pair.first);
    }

    return result;
}


// We are a simple delegator.
IntermediateMappingOutput ConverterRegistry::convert(ConverterName c, string value, OptionsMap options) {
    auto iter = converterMap.find(c);
    if (iter == converterMap.end()) {
        throw std::runtime_error("converter not found");
    } else {
        Converter* converter = converterMap.at(c);
        return converter->applyConversion(value, options);
    }
}

// CONVERSION METHODS:
IntermediateMappingOutput DiscardConverter::applyConversion(string value, OptionsMap options) {
    QJsonValue producedValue;
    vector<string> producedPaths;
    IntermediateMappingOutput result(producedValue, producedPaths, CombinationOperation::DISCARD);
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

IntermediateMappingOutput ListOfStringConverter::applyConversion(string input, OptionsMap options) {
    QJsonValue producedValue;        // Will be initialized to null.
    vector<string> producedPaths;    // We won't produce any paths.
    
    optional<string> delimiter = options.at("delimiter");

    QJsonArray keywordsArray;

    if (delimiter.has_value()) {
        string delimiterRegex = delimiter.value();
        vector<string> keywords = splitByRegexp(input, delimiterRegex);
        for (string k: keywords) {
            keywordsArray.append(QJsonValue(QString::fromStdString(k)));
        }
    } else {
        keywordsArray.append(QJsonValue(QString::fromStdString(input)));
    }

    producedValue = keywordsArray;

    qDebug() << producedValue;

    IntermediateMappingOutput result(
        keywordsArray, producedPaths, CombinationOperation::CONJOIN
    );
    return result;
}

// LOOKUP REGISTRY

LookupRegistryImpl::LookupRegistryImpl() {
    // unused as yet due to hacks
    definedTypeMap.insert({"Figure", "figure"});
}

LookupRegistryImpl::~LookupRegistryImpl() {
}

QJsonValue LookupRegistryImpl::lookupByString(LookupType type, string value) {
    QJsonValue result;

    // Now we need to look it up using LookupType.

    if (type == LookupType::DEFINED_TYPE) {
        string figshareName = definedTypeMap.at(value);
        return QJsonValue(QString::fromStdString(figshareName));
    } else {
        throw new std::runtime_error("invalid lookup type");
    }


    return result;
}
