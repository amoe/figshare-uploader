#include <gmock/gmock.h>
#include "file_info.hh"
#include "io_slicer.hh"
#include "part_preparer.hh"

using ::testing::Eq;

TEST(PartPreparerTest, ActsAsIExpect) {
    // Dependency
    // some issue here because the fileinfo needs to also contain the data...

    IOSlicer *slicer = new FileSlicer("lena.jpg");
    PartPreparer preparer(slicer);
    FileInfo fileInfo("http://my-site.com/", "lena.jpg");

    FilePart filePart(
        42, 2, 8, false, FilePartStatus::PENDING
    );

    ASSERT_THAT(filePart.getStartOffset(), Eq(2));
    ASSERT_THAT(filePart.getEndOffset(), Eq(8));

    UploadCommand result = preparer.prepareUpload(fileInfo, filePart);

    ASSERT_THAT(result.getUrl(), Eq("lena.jpg/42"));
    ASSERT_THAT(result.getData().size(), Eq(6));

}

