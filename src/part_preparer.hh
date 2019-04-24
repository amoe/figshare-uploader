#ifndef PART_PREPARER_HH
#define PART_PREPARER_HH
#include "upload_command.hh"
#include "file_part.hh"
#include "file_info.hh"

class PartPreparer {
public:
    virtual UploadCommand prepareUpload(
        const string sourcePath, const FileInfo info, const FilePart part
    ) = 0;
};


class PartPreparerImpl : public PartPreparer {
public:
    PartPreparerImpl() { }
    UploadCommand prepareUpload(const string sourcePath, const FileInfo info, const FilePart part);

private:
    vector<char> getDataSlice(string filePath, int64_t startOffset, int64_t endOffset);
};


#endif // PART_PREPARER_HH
