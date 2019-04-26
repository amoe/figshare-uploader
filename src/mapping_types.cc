#include <stdexcept>
#include <sstream>
#include "mapping_types.hh"
#include <QDebug>

using std::runtime_error;
using std::ostringstream;

OptionsMap FieldEncoder::getOptions() const {
    return options;
}

bool FieldEncoder::operator==(const FieldEncoder& other) const {
    return targetField == other.getTargetField()
        && converterName == other.getConverterName()
        && validationRules == other.getValidationRules()
        && options == other.getOptions();
}

optional<TargetField> FieldEncoder::getTargetField() const {
    return targetField;
}

ConverterName FieldEncoder::getConverterName() const {
    return converterName;
}


string TargetField::getName() const {
    return name;
}

TargetFieldType TargetField::getTargetFieldType() const {
    return type;
}

bool TargetField::operator==(const TargetField& other) const {
    return type == other.getTargetFieldType() && name == other.getName();
}

// Mapping output types

QJsonObject MappingOutput::getArticleObject() const {
    return articleObject;
}

vector<string> MappingOutput::getSourcePaths() const {
    return sourcePaths;
}

// Intermediate stuff

vector<string> IntermediateMappingOutput::getProducedPaths() const {
    return producedPaths;
}

QJsonValue IntermediateMappingOutput::getProducedValue() const {
    return producedValue;
}

CombinationOperation IntermediateMappingOutput::getOperation() const {
    return operation;
}

// Field encoder application

MappingOutput FieldEncoder::applyEncoder(MappingOutput seed, IntermediateMappingOutput operand) const {
    // Start with a copy.
    QJsonObject newArticleObject(seed.getArticleObject());
    vector<string> newSourcePaths(seed.getSourcePaths());

    switch (operand.getOperation()) {
        case CombinationOperation::CONJOIN:
            handleConjoin(newArticleObject, newSourcePaths, operand);
            break;
        case CombinationOperation::DISCARD:
            break;
        default:
            throw runtime_error("unexpected combination operation");
    }
    
    MappingOutput result(newArticleObject, newSourcePaths);
    return result;
}


void FieldEncoder::handleConjoin(
    QJsonObject& newArticleObject, vector<string>& newSourcePaths,
    IntermediateMappingOutput operand
) const {
    if (targetField.has_value()) {
        TargetField field = targetField.value();
        QString fieldName = QString::fromStdString(field.getName());
        qDebug() << "fieldname:" << fieldName;

        switch (field.getTargetFieldType()) {
            case TargetFieldType::STANDARD: {
                newArticleObject.insert(fieldName, operand.getProducedValue());
                break;
            }
            case TargetFieldType::CUSTOM: {
                QJsonValue existingCustomFields = newArticleObject.value("custom_fields");
                QJsonObject newCustomFields(existingCustomFields.toObject());
                newCustomFields.insert(fieldName, operand.getProducedValue());
                newArticleObject["custom_fields"] = newCustomFields;
                break;
            }
            default:
                throw runtime_error("invalid target field type");
        }
    }

    vector<string> producedPaths = operand.getProducedPaths();

    // Always extend the source paths with the produced ones.
    // If there weren't any contributed files, newSourcePaths is just
    // an empty vector, so this is a no-op.
    newSourcePaths.insert(
        newSourcePaths.end(),
        producedPaths.begin(),
        producedPaths.end()
    );
}

vector<ValidationRule> FieldEncoder::getValidationRules() const {
    return validationRules;
}

// Return a string description of the field encoder
string FieldEncoder::describe() const {
    ConverterNameBijectiveMapper mapper;    // XXX: Extremely wasteful
    string converterNameString = mapper.getSerializableName(converterName);

    ostringstream descriptionStream;

    if (targetField.has_value()) {
        descriptionStream << targetField.value().getName()
                          << " ";
    }

    descriptionStream << "[" << converterNameString << "]";
    return descriptionStream.str();
}
