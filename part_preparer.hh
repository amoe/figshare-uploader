#ifndef PART_PREPARER_HH
#define PART_PREPARER_HH

#include <gmock/gmock.h>
#include "upload_command.hh"
#include "file_part.hh"
#include "file_info.hh"
#include "io_slicer.hh"

class PartPreparer {
public:
    virtual UploadCommand prepareUpload(
        const FileInfo info, const FilePart part
    ) = 0;
};


class PartPreparerImpl : public PartPreparer {
public:
    PartPreparerImpl(IOSlicer* slicer) : slicer(slicer) { }
    UploadCommand prepareUpload(const FileInfo info, const FilePart part);

private:
    IOSlicer *slicer;
};

class MockPartPreparer : public PartPreparer {
public:
    MOCK_METHOD2(
        prepareUpload,
        UploadCommand(const FileInfo info, const FilePart part)
    );
};

#endif // PART_PREPARER_HH
