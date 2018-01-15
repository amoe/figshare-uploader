#include <gmock/gmock.h>
#include "file_info.hh"
#include "raw_literals.hh"

using ::testing::Eq;

TEST(FileInfoTest, DeserializesFromJson) {
    FileInfo info = FileInfo::fromJson(raw_literals::serializedFileInfo);

    ASSERT_THAT(info.id, Eq(9993997));
    ASSERT_THAT(
        info.uploadContainerUrl,
        Eq("https://fup100010.figshare.com/upload/af4a43ba-1253-4960-8d5a-8b3ed971e9e8")
    );
    ASSERT_THAT(
        info.fileName,
        Eq("pb_lc_bcr_c18980000-0004aa.tiff")
    );
}







