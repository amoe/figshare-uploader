#include <stdexcept>
#include "mapping_types.hh"

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
            throw std::runtime_error("unexpected combination operation");
    }
    
    MappingOutput result(newArticleObject, newSourcePaths);
    return result;
}


void FieldEncoder::handleConjoin(
    QJsonObject& newArticleObject, vector<string>& newSourcePaths,
    IntermediateMappingOutput operand
) const {
    if (targetField.has_value()) {
        // FIXME: We don't handle custom fields yet!
        TargetField field = targetField.value();
        newArticleObject.insert(
            QString::fromStdString(field.getName()), operand.getProducedValue()
        );
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
    string result;
    result = mapper.getSerializableName(converterName);
    return result;
}
