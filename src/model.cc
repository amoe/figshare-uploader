#include <iostream>
#include "model.hh"

Model::Model() {
    this->sourceFile = nullopt;
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
