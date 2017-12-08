#include <gmock/gmock.h>
#include "test_utility.hh"
#include "fake_qt_core_application.hh"
#include "raw_literals.hh"
#include "http_getter.hh"

using std::string;
using ::testing::Eq;

TEST(HttpGetter, GetsTheByteArraySuccessfully) {
    bootQtEventLoop();
    HttpGetter* getter = new QtHttpGetter;
    string body = getter->request("https://httpbin.org/user-agent");

    std::cout << body << std::endl;

    ASSERT_THAT(
        deserialize(body),
        Eq(deserialize(raw_literals::httpbinResponse))
    );

}

