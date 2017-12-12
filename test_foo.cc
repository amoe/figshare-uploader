#include <iostream>
#include "http_poster.hh"
#include <QApplication>
#include "raw_literals.hh"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    HttpPoster* poster = new QtHttpPoster;
    string reply = poster->request("https://api.figshare.com/v2/account/articles", raw_literals::generatedRequest);
    std::cout << reply << std::endl;
}
