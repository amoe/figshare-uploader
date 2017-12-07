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
#include "test_utility.hh"
#include "raw_literals.hh"
#include "fake_qt_core_application.hh"

using std::string;

using ::testing::Eq;

class HttpGetter {
public:
    virtual string request(const string url) = 0;
};

class QtHttpGetter : public HttpGetter {
public:
    string request(const string url);
};

string QtHttpGetter::request(const string url) {
    QEventLoop waitLoop;

    QUrl endpoint(QString::fromStdString(url));

    QNetworkAccessManager manager;
    QNetworkRequest request(endpoint);

    QNetworkReply* reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit);
    waitLoop.exec();
    QByteArray result = reply->readAll();

    return QString(result).toStdString();
}

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

