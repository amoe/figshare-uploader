#include <cstdint>
#include "file_part.hh"

int FilePart::getPartNumber() const {
    return this->partNumber;
}

int64_t FilePart::getStartOffset() const {
    return this->startOffset;
}

int64_t FilePart::getEndOffset() const {
    return this->endOffset;
}
