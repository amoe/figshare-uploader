#include <gmock/gmock.h>
#include "fake_qt_core_application.hh"
#include "http_poster.hh"
#include "utility.hh"
#include "mocks.hh"

using ::testing::Eq;
using std::string;

TEST(HttpPoster, DISABLED_CanPost) {
    bootQtEventLoop();
    MockTokenStore store;
    HttpPoster* poster = new QtHttpPoster(&store);
    string body = poster->request("https://httpbin.org/post", "nonesuch");

    std::cout << body << std::endl;

    ASSERT_THAT(fetchString(body, "data"), Eq("nonesuch"));
}

