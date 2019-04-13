#include <gmock/gmock.h>
#include "file_info.hh"
#include "part_preparer.hh"

using ::testing::Eq;

// nb this is an integration test
TEST(PartPreparerTest, CanPrepareUpload) {
    PartPreparerImpl preparer;
    FileInfo fileInfo("http://my-site.com/my-token", "lena.jpg", 1);

    FilePart filePart(
        42, 2, 8, false, FilePartStatus::PENDING
    );

    ASSERT_THAT(filePart.getStartOffset(), Eq(2));
    ASSERT_THAT(filePart.getEndOffset(), Eq(8));

    UploadCommand result = preparer.prepareUpload("lena.jpg", fileInfo, filePart);

    ASSERT_THAT(result.getUrl(), Eq("http://my-site.com/my-token/42"));

    // This is insanely weird but the offset from 2 to 8 should actually be 1
    // larger for some reason.  This is an oddity of Figshare, AFAICS, unless
    // I'm just being an idiot.
    ASSERT_THAT(result.getData().size(), Eq(7));

}

