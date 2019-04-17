#include <gmock/gmock.h>
#include "upload_container_info.hh"
#include "raw_literals.hh"
#include "file_part.hh"
#include "test_vocabulary.hh"

TEST(UploadContainerInfoTest, DeserializesCorrectly) {
    UploadContainerInfo info = UploadContainerInfo::fromJson(
        raw_literals::serializedUploadContainerInfo
    );


    // This can't be tested at the moment, because file parts aren't comparable.
    // vector<FilePart> expectedParts;
    // ASSERT_THAT(info.parts,Eq(expectedParts));

    
    ASSERT_THAT(info.md5, Eq("7b6a523ae2adc8ed0f55e7bb27f39ffc"));
    ASSERT_THAT(info.name, Eq("9981382/pb_lc_bcr_c189800000004aa.tiff"));
    ASSERT_THAT(info.size, Eq(23561500));
    ASSERT_THAT(info.status, Eq(UploadContainerStatus::PENDING));
    ASSERT_THAT(info.token, Eq("1d71cd99-6695-420e-884a-e889571b307b"));
}


