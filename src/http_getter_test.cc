#include <gmock/gmock.h>
#include "test_utility.hh"
#include "fake_qt_core_application.hh"
#include "raw_literals.hh"
#include "http_getter.hh"
#include "token_store.hh"
#include "mocks.hh"
#include "logging.hh"
#include "test_vocabulary.hh"

using std::string;

TEST(HttpGetter, GetsTheByteArraySuccessfully) {
    bootQtEventLoop();
    MockTokenStore store;
    HttpGetter* getter = new QtHttpGetter(&store);
    string body = getter->request("https://httpbin.org/user-agent");

    spdlog::info("full response body: {}", body);

    ASSERT_THAT(
        deserialize(body),
        Eq(deserialize(raw_literals::httpbinResponse))
    );

}

