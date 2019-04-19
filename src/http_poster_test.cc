#include <gmock/gmock.h>
#include "fake_qt_core_application.hh"
#include "http_poster.hh"
#include "utility.hh"


using ::testing::Eq;
using std::string;

TEST(HttpPoster, DISABLED_CanPost) {
    bootQtEventLoop();
    TokenStore store("NOT USED");
    HttpPoster* getter = new QtHttpPoster(&store);
    string body = getter->request("https://httpbin.org/post", "nonesuch");

    std::cout << body << std::endl;

    ASSERT_THAT(fetchString(body, "data"), Eq("nonesuch"));
}

