#include <gmock/gmock.h>
#include "fake_qt_core_application.hh"
#include "http_poster.hh"
#include "utility.hh"
#include "mocks.hh"
#include "logging.hh"

using ::testing::Eq;
using std::string;

TEST(HttpPoster, CanPost) {
    bootQtEventLoop();
    MockTokenStore store;
    HttpPoster* poster = new QtHttpPoster(&store);

    string body = poster->request("https://httpbin.org/post", "nonesuch");
    spdlog::info("full response body: {}", body);

    ASSERT_THAT(fetchString(body, "data"), Eq("nonesuch"));
}

