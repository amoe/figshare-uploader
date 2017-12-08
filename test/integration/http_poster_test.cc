#include <string>
#include <gmock/gmock.h>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QCoreApplication>
#include <QEventLoop>
#include <QObject>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include "fake_qt_core_application.hh"
#include "raw_literals.hh"
#include "test_utility.hh"

using ::testing::Eq;
using std::string;

class HttpPoster {
public:
    virtual string request(const string url, const string payload) = 0;
};

class QtHttpPoster : public HttpPoster {
public:
    string request(const string url, const string payload);
};

string QtHttpPoster::request(const string url, const string payload) {
    QEventLoop waitLoop;

    QUrl endpoint(QString::fromStdString(url));

    QNetworkAccessManager manager;
    QNetworkRequest request(endpoint);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray content =  QString::fromStdString(payload).toUtf8();
    QNetworkReply* reply = manager.post(request, content);

    QObject::connect(reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit);
    waitLoop.exec();
    QByteArray result = reply->readAll();

    return QString(result).toStdString();
}


TEST(HttpPoster, CanPost) {
    bootQtEventLoop();
    HttpPoster* getter = new QtHttpPoster;
    string body = getter->request("https://httpbin.org/post", "nonesuch");

    std::cout << body << std::endl;

    ASSERT_THAT(fetchString(body, "data"), Eq("nonesuch"));
}

