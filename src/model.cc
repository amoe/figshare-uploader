#include <iostream>
#include "model.hh"

ModelImpl::ModelImpl() {
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

ModelImpl::~ModelImpl() {
}

void ModelImpl::setSourceFile(string newSourceFile) {
    this->sourceFile = optional<string>(newSourceFile);
}

optional<string> ModelImpl::getSourceFile() const {
    return this->sourceFile;
}

vector<FieldEncoder>& ModelImpl::getAvailableEncoders() {
    return availableEncoders;
}

void ModelImpl::addFieldEncoder(FieldEncoder f) {
    availableEncoders.push_back(f);
    std::cout << "size of encoders list is now " << availableEncoders.size() << std::endl;
    std::cout << "address in model is " << &availableEncoders << std::endl;
}

