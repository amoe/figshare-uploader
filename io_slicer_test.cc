#include <gmock/gmock.h>
#include <cstddef>
#include "io_slicer.hh"

using ::testing::Eq;

TEST(IoSlicerTest, ActsAsIExpect) {
    IOSlicer *slicer = new FileSlicer("lena.jpg");
    
    std::vector<std::byte> buf = slicer->getDataSlice(2, 4);

    // Now the size should be 2.

    ASSERT_THAT(buf.size(), Eq(2));
    ASSERT_THAT(buf.at(0), Eq(std::byte{0xff}));
    ASSERT_THAT(buf.at(1), Eq(std::byte{0xe0}));
}

