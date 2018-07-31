#include <iostream>
#include <gmock/gmock.h>
#include <string>

#include "group_mapper.hh"
#include "http_getter.hh"

using namespace testing;
// what do we want?  a simple map that maintains a groupNameToId() method
// and we'll mock out the httpgetter to patch in the request



TEST(MyComponent, ActsAsIExpect) {
    MockHttpGetter httpGetter;

    string mockedResult = "{}";

    EXPECT_CALL(httpGetter, request(_))
        .WillOnce(Return(mockedResult));
    
    ASSERT_THAT(2 + 2, Eq(4));
}

