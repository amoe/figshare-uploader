#include <gmock/gmock.h>


TEST(HttpGetter, GetsTheByteArraySuccessfully) {
    HttpGetter* getter = new QtHttpGetter;
    
    std::string body = getter->request("https://httpbin.org/user-agent");

    ASSERT_THAT(
        deserialize(serializedResult),
        Eq(deserialize(raw_literals::expectedResult))
    );

}

