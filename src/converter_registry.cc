#include <stdexcept>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <iostream>
#include "converter_registry.hh"
#include "utility.hh"

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
    LookupType type = LOOKUP_TYPE_NAMES.at(resourceName);
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

    if (delimiter.has_value()) {
        string delimiterRegex = delimiter.value();
        vector<string> discreteValues = splitByRegexp(input, delimiterRegex);
        for (string v: discreteValues) {
            resultArray.append(QJsonValue(QString::fromStdString(v)));
        }
    } else {
        resultArray.append(QJsonValue(QString::fromStdString(input)));
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
    CategoryMapper* categoryMapper, GroupMapper* groupMapper
) {
    // unused as yet due to hacks
    definedTypeMap.insert({"Figure", "figure"});
    this->categoryMapper = categoryMapper;
    this->groupMapper = groupMapper;
}

LookupRegistryImpl::~LookupRegistryImpl() {
}

QJsonValue LookupRegistryImpl::lookupByString(LookupType type, string value) {
    // Now we need to look it up using LookupType.
    switch (type) {
        case LookupType::DEFINED_TYPE: {
            string figshareName = definedTypeMap.at(value);
            return QJsonValue(QString::fromStdString(figshareName));
        }
        case LookupType::CATEGORY: {
            return QJsonValue(categoryMapper->mapTitle(value));
        }
        case LookupType::GROUP: {
            return QJsonValue(groupMapper->getGroupIdByName(value));
        }
        default:
            throw new std::runtime_error("invalid lookup type");
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
