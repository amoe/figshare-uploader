#include <gmock/gmock.h>
#include "upload_container_info.hh"
#include "raw_literals.hh"

using ::testing::Eq;

TEST(UploadContainerInfoTest, DeserializesCorrectly) {
    std::cout << raw_literals::serializedUploadContainerInfo;

}


