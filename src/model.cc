#include <iostream>
#include "model.hh"

void Model::setSourceFile(string newSourceFile) {
    this->sourceFile = optional<string>(newSourceFile);
}

optional<string> Model::getSourceFile() const {
    return this->sourceFile;
}
