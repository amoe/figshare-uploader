#include "upload_command.hh"
#include "file_part.hh"
#include "file_info.hh"
#include "io_slicer.hh"

class PartPreparer {
public:
    PartPreparer(IOSlicer* slicer) : slicer(slicer) { }
    UploadCommand prepareUpload(const FileInfo info, const FilePart part);

private:
    IOSlicer *slicer;
};
