#include <iostream>
#include "part_preparer.hh"

UploadCommand PartPreparer::prepareUpload(
    const FileInfo info, const FilePart part
) {
    std::string fileName = info.fileName;
    std::string url = 
        info.uploadContainerUrl + "/" + std::to_string(part.getPartNumber());

    
    int64_t start = part.getStartOffset();
    int64_t end = part.getEndOffset();

    std::cout << "will try start" << start << std::endl;
    std::cout << "will try end" << end << std::endl;

    std::vector<char> data = this->slicer->getDataSlice(
        part.getStartOffset(), part.getEndOffset()
    );

    return UploadCommand(url, data);
}
