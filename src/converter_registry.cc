#include <stdexcept>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <iostream>
#include "converter_registry.hh"
#include "utility.hh"

using std::runtime_error;

ConverterRegistry::ConverterRegistry() {}
ConverterRegistry::~ConverterRegistry() {}

void ConverterRegistry::registerConverter(ConverterName symbolicName, Converter* implementation) {
    converterMap.insert({symbolicName, implementation});
}

const vector<ConverterName> ConverterRegistry::getRegisteredConverters() const {
    vector<ConverterName> result;

    for (const auto& pair: converterMap) {
        result.push_back(pair.first);
    }

    return result;
}


// We are a simple delegator.
IntermediateMappingOutput ConverterRegistry::convert(
    ConverterName c, string value, OptionsMap options
) {
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

IntermediateMappingOutput LookupValueConverter::applyConversion(string input, OptionsMap options) {
    string resourceName = options.at("resourceName").value();

    auto it = LOOKUP_TYPE_NAMES.find(resourceName);
    if (it == LOOKUP_TYPE_NAMES.end()) {
        throw runtime_error("resource name not found, check field encoder definition");
    }
    
    
    LookupType type = it->second;
    QJsonValue producedValue = registry->lookupByString(type, input);
    vector<string> producedPaths;
    IntermediateMappingOutput result(producedValue, producedPaths, CombinationOperation::CONJOIN);
    return result;
}

IntermediateMappingOutput LookupListConverter::applyConversion(
    string input, OptionsMap options
) {
    string resourceName = options.at("resourceName").value();
    LookupType type = LOOKUP_TYPE_NAMES.at(resourceName);

    vector<string> producedPaths;
    QJsonArray producedValue;
    producedValue.append(registry->lookupByString(type, input));

    IntermediateMappingOutput result(
        producedValue, producedPaths, CombinationOperation::CONJOIN
    );
    return result;
}

IntermediateMappingOutput ListOfObjectConverter::applyConversion(
    string input, OptionsMap options
) {
    QJsonValue producedValue;        // Will be initialized to null.
    vector<string> producedPaths;    // We won't produce any paths.

    string objectField = options.at("objectField").value();
    optional<string> delimiter = options.at("delimiter");

    QJsonArray resultArray;

    if (delimiter.has_value()) {
        string delimiterRegex = delimiter.value();
        vector<string> discreteValues = splitByRegexp(input, delimiterRegex);
        for (string v: discreteValues) {
            QJsonObject containerObject;
            containerObject.insert(
                QString::fromStdString(objectField),
                QJsonValue(QString::fromStdString(v))
            );

            resultArray.append(containerObject);
        }
    } else {
        QJsonObject containerObject;
        containerObject.insert(
            QString::fromStdString(objectField),
            QJsonValue(QString::fromStdString(input))
        );
        resultArray.append(containerObject);
    }

    producedValue = resultArray;

    IntermediateMappingOutput result(
        resultArray, producedPaths, CombinationOperation::CONJOIN
    );
    return result;
}

IntermediateMappingOutput ListOfStringConverter::applyConversion(string input, OptionsMap options) {
    QJsonValue producedValue;        // Will be initialized to null.
    vector<string> producedPaths;    // We won't produce any paths.
    
    optional<string> delimiter = options.at("delimiter");

    QJsonArray resultArray;

    if (input.empty()) {
        // Ignore empty input and produce a zero-element array.
    } else {
        if (delimiter.has_value()) {
            string delimiterRegex = delimiter.value();
            vector<string> discreteValues = splitByRegexp(input, delimiterRegex);
            for (string v: discreteValues) {
                resultArray.append(QJsonValue(QString::fromStdString(v)));
            }
        } else {
            resultArray.append(QJsonValue(QString::fromStdString(input)));
        }
    }

    producedValue = resultArray;

    qDebug() << producedValue;

    IntermediateMappingOutput result(
        producedValue, producedPaths, CombinationOperation::CONJOIN
    );
    return result;
}

// LOOKUP REGISTRY

LookupRegistryImpl::LookupRegistryImpl(
    CategoryMapper* categoryMapper, GroupMapper* groupMapper, LicenseMapper* licenseMapper
) {
    // There may be more.
    definedTypeMap.insert({"Figure", "figure"});
    definedTypeMap.insert({"Dataset", "dataset"});
    definedTypeMap.insert({"Media", "media"});
    definedTypeMap.insert({"Poster", "poster"});
    definedTypeMap.insert({"Paper", "paper"});
    definedTypeMap.insert({"Fileset", "fileset"});

    this->categoryMapper = categoryMapper;
    this->groupMapper = groupMapper;
    this->licenseMapper = licenseMapper;
}

LookupRegistryImpl::~LookupRegistryImpl() {
}

QJsonValue LookupRegistryImpl::lookupByString(LookupType type, string value) {
    switch (type) {
        case LookupType::DEFINED_TYPE: {
            auto it = definedTypeMap.find(value);
            if (it == definedTypeMap.end()) {
                throw std::runtime_error("unknown value in defined type converter");
            } else {
                return QJsonValue(QString::fromStdString(it->second));
            }

        }
        case LookupType::CATEGORY: {
            return QJsonValue(categoryMapper->mapTitle(value));
        }
        case LookupType::GROUP: {
            return QJsonValue(groupMapper->getGroupIdByName(value));
        }
        case LookupType::LICENSE: {
            return QJsonValue(licenseMapper->mapName(value));
        }
        default:
            throw std::runtime_error("invalid lookup type");
    }
}



void ConverterRegistry::initializeStandardConverters(
    ConverterRegistry& r,  LookupRegistry* lookupRegistry
) {
    r.registerConverter(ConverterName::STRING, new StringConverter);
    r.registerConverter(ConverterName::CONTRIBUTE_FILES, new ContributeFilesConverter);

    // Lookup list needs more information to initialize itself.
    r.registerConverter(
        ConverterName::LOOKUP_VALUE, new LookupValueConverter(lookupRegistry)
    );
    r.registerConverter(
        ConverterName::LOOKUP_LIST, new LookupListConverter(lookupRegistry)
    );
    r.registerConverter(ConverterName::DISCARD, new DiscardConverter);
    r.registerConverter(ConverterName::LIST_OF_STRING, new ListOfStringConverter);
    r.registerConverter(ConverterName::LIST_OF_OBJECT, new ListOfObjectConverter);
}
