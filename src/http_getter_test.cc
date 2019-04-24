#include <gmock/gmock.h>
#include "test_utility.hh"
#include "fake_qt_core_application.hh"
#include "raw_literals.hh"
#include "http_getter.hh"
#include "token_store.hh"
#include "mocks.hh"

using std::string;
using ::testing::Eq;

TEST(HttpGetter, DISABLED_GetsTheByteArraySuccessfully) {
    bootQtEventLoop();
    MockTokenStore store;
    HttpGetter* getter = new QtHttpGetter(&store);
    string body = getter->request("https://httpbin.org/user-agent");

    std::cout << body << std::endl;

    ASSERT_THAT(
        deserialize(body),
        Eq(deserialize(raw_literals::httpbinResponse))
    );

}

