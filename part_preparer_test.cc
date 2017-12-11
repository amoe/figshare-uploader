#include <gmock/gmock.h>
#include "file_info.hh"
#include "io_slicer.hh"
#include "part_preparer.hh"

TEST(PartPreparerTest, ActsAsIExpect) {
    // Dependency
    // some issue here because the fileinfo needs to also contain the data...

    IOSlicer *slicer = new FileSlicer("/home/amoe/cpp-netlib-build.tar");
    PartPreparer preparer(slicer);
    FileInfo fileInfo("http://my-site.com/", "/home/amoe/cpp-netlib-build.tar");

    FilePart filePart(
        42, 2, 8, false, FilePartStatus::PENDING
    );

    std::cout << "start offset is " << filePart.getStartOffset() << std::endl;
    std::cout << "end offset is " << filePart.getEndOffset() << std::endl;

    UploadCommand result = preparer.prepareUpload(fileInfo, filePart);

    std::cout << "upload url: " << result.getUrl() << std::endl;
    std::cout << "upload size: " << result.getData().size() << std::endl;
}

