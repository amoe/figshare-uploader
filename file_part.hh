#ifndef FILE_PART_HH
#define FILE_PART_HH

#include <cstdint>
#include <string>
#include <vector>
#include <QJsonObject>

using std::string;
using std::vector;

enum class FilePartStatus { PENDING, COMPLETED, ABORTED };

class FilePart {
public:
    FilePart(
        int partNumber,
        int64_t startOffset,
        int64_t endOffset,
        bool isLocked,
        FilePartStatus status
    ) : partNumber(partNumber), startOffset(startOffset), endOffset(endOffset),
        isLocked_(isLocked), status(status) {}

    int getPartNumber() const;
    int64_t getStartOffset() const;
    int64_t getEndOffset() const;
    FilePartStatus getStatus() const;
    bool isLocked() const;
    static FilePart fromJson(QJsonObject object);

private:
    static FilePartStatus mapStatus(string status);

    int partNumber;
    int64_t startOffset;
    int64_t endOffset;
    bool isLocked_;
    FilePartStatus status;
};

#endif
