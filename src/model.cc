#include <iostream>
#include "model.hh"

Model::Model() {
    this->sourceFile = nullopt;

    // Initialize standard field encoders
    TargetField targetField(TargetFieldType::STANDARD, "title");
    FieldEncoder titleEncoder(
        optional<TargetField>(targetField),
        ConverterName::STRING,
        {},
        {}
    );
    availableEncoders = {titleEncoder};
}

Model::~Model() {
}

void Model::setSourceFile(string newSourceFile) {
    this->sourceFile = optional<string>(newSourceFile);
}

optional<string> Model::getSourceFile() const {
    return this->sourceFile;
}

vector<FieldEncoder>& Model::getAvailableEncoders() {
    return availableEncoders;
}
