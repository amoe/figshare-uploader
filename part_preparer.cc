#include <iostream>
#include "part_preparer.hh"
#include "logging.hh"

UploadCommand PartPreparer::prepareUpload(
    const FileInfo info, const FilePart part
) {
    std::string fileName = info.fileName;
    std::string url = 
        info.uploadContainerUrl + "/" + std::to_string(part.getPartNumber());

    
    int64_t start = part.getStartOffset();
    int64_t end = part.getEndOffset();

    debugf("will try start: %d", start);
    debugf("will try end: %d", end);

    std::vector<char> data = this->slicer->getDataSlice(
        part.getStartOffset(),
        part.getEndOffset() + 1   // See test for notes on this
    );

    return UploadCommand(url, data);
}
