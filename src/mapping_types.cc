#include <stdexcept>
#include "mapping_types.hh"

int RowMapping::getSourceRowIndex() const {
    return sourceRowIndex;
}

FieldEncoder RowMapping::getFieldEncoder() const {
    return fieldEncoder;
}

OptionsMap FieldEncoder::getOptions() const {
    return options;
}

ConverterName FieldEncoder::getConverterName() const {
    return converterName;
}


string TargetField::getName() const {
    return name;
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
    
    QJsonValue producedValue = operand.getProducedValue();
    vector<string> producedPaths = operand.getProducedPaths();

    if (operand.getOperation() == CombinationOperation::CONJOIN) {
        if (targetField.has_value()) {
            // FIXME: We don't handle custom fields yet!
            TargetField field = targetField.value();
            newArticleObject.insert(
                QString::fromStdString(field.getName()), producedValue
            );
        }

        // Always extend the source paths with the produced ones.
        // If there weren't any contributed files, newSourcePaths is just
        // an empty vector, so this is a no-op.
        newSourcePaths.insert(
            newSourcePaths.end(),
            producedPaths.begin(),
            producedPaths.end()
        );
    } else {
        // We only support CONJOIN at present.
        // Other possibilities might be, like, NUKE or something which would
        // just annul an existing field.
        throw std::runtime_error("unexpected combination operation");
    }
    
    MappingOutput result(newArticleObject, newSourcePaths);
    return result;
}
