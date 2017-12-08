#include <gmock/gmock.h>
#include "fake_qt_core_application.hh"
#include "http_poster.hh"
#include "utility.hh"


using ::testing::Eq;
using std::string;

TEST(HttpPoster, CanPost) {
    bootQtEventLoop();
    HttpPoster* getter = new QtHttpPoster;
    string body = getter->request("https://httpbin.org/post", "nonesuch");

    std::cout << body << std::endl;

    ASSERT_THAT(fetchString(body, "data"), Eq("nonesuch"));
}

