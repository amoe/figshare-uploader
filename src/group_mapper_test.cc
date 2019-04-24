#include <iostream>
#include <gmock/gmock.h>
#include <string>
#include "mocks.hh"
#include "group_mapper.hh"
#include "http_getter.hh"
#include "raw_literals.hh"

using namespace testing;
// what do we want?  a simple map that maintains a groupNameToId() method
// and we'll mock out the httpgetter to patch in the request



TEST(MyComponent, CanRequestGroupId) {
    MockHttpGetter httpGetter;

    EXPECT_CALL(httpGetter, request(_))
        .WillOnce(Return(raw_literals::groupApiResponse));

    GroupMapperImpl groupMapper(&httpGetter);
    
    int groupId = groupMapper.getGroupIdByName("The Planet Bethlehem Archive");

    ASSERT_THAT(groupId, Eq(11611));
}

