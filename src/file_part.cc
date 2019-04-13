#include <stdexcept>
#include <cstdint>
#include <map>
#include "file_part.hh"

using std::string;
using std::map;

int FilePart::getPartNumber() const {
    return this->partNumber;
}

int64_t FilePart::getStartOffset() const {
    return this->startOffset;
}

int64_t FilePart::getEndOffset() const {
    return this->endOffset;
}

FilePartStatus FilePart::getStatus() const {
    return this->status;
}

bool FilePart::isLocked() const {
    return this->isLocked_;
}


FilePart FilePart::fromJson(QJsonObject object) {
    int partNumber;
    int64_t startOffset;
    int64_t endOffset;
    bool isLocked;
    FilePartStatus status;

    partNumber = object.value("partNo").toInt();
    startOffset = object.value("startOffset").toInt();
    endOffset = object.value("endOffset").toInt();
    isLocked = object.value("locked").toBool();
    status = mapStatus(object.value("status").toString().toStdString());

    return FilePart(partNumber, startOffset, endOffset, isLocked, status);
}

FilePartStatus FilePart::mapStatus(string status) {
    map<string, FilePartStatus> statuses = {
        {"PENDING", FilePartStatus::PENDING},
        {"COMPLETED", FilePartStatus::COMPLETED},
        {"ABORTED", FilePartStatus::ABORTED}
    };

    auto it = statuses.find(status);
    if (it == statuses.end()) {
        throw std::runtime_error("file part status not found");
    } else {
        return it->second;
    }
}
