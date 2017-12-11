#ifndef FILE_PART_HH
#define FILE_PART_HH

#include <cstdint>

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
        isLocked(isLocked), status(status) {}

    int getPartNumber() const;
    int64_t getStartOffset() const;
    int64_t getEndOffset() const;
private:
    int partNumber;
    int64_t startOffset;
    int64_t endOffset;
    bool isLocked;
    FilePartStatus status;
};

#endif
