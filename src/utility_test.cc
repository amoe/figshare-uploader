#include <gmock/gmock.h>
#include "utility.hh"

using namespace testing;


TEST(UtilityTest, CanResolvePath) {
    string base = "/home/john-smith/my stuff/upload specification.xlsx";
    string relative = "my upload.png";

    string result = resolvePath(base, relative);
    
    ASSERT_THAT(
        resolvePath(base, relative),
        Eq("/home/john-smith/my stuff/my upload.png")
    );
}


