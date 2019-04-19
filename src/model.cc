#include <iostream>
#include "model.hh"
#include "default_field_encoders.hh"

ModelImpl::ModelImpl() {
    this->sourceFile = nullopt;


    availableEncoders = {
        default_field_encoders::DISCARD_ENCODER,
        default_field_encoders::TITLE_ENCODER
    };
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

