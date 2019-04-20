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

const optional<string> ModelImpl::getSourceFile() const {
    return this->sourceFile;
}

vector<FieldEncoder>& ModelImpl::getAvailableEncoders() {
    return availableEncoders;
}

void ModelImpl::addFieldEncoder(FieldEncoder f) {
    availableEncoders.push_back(f);
}

void ModelImpl::bindRow(int excelRow, int fieldEncoderIndex) {
    std::cout << "I would bind row " << excelRow << " to field encoder with index " << fieldEncoderIndex << std::endl;
    // This will give a runtime failure.
    fieldMappings.at(excelRow) = availableEncoders.at(fieldEncoderIndex);
}

void ModelImpl::setHeaderFields(vector<string> headerFields) {
    this->headerFields = headerFields;
    initializeMappingScheme();
}

const vector<string> ModelImpl::getHeaderFields() const {
    return headerFields;
}

void ModelImpl::initializeMappingScheme() {
    fieldMappings.resize(
        headerFields.size(), default_field_encoders::DISCARD_ENCODER
    );
}

void ModelImpl::dumpMappingScheme() const {
    cout << "START MAPPING SCHEME DUMP: " << "[" << endl;

    for (int i = 0; i < fieldMappings.size(); i++) {
        FieldEncoder theEncoder = fieldMappings.at(i);
        std::cout << "    Index " << i << ": " << theEncoder.describe() << endl;
    }
    
    cout << "] END MAPPING SCHEME DUMP" << endl;
}
