#include <stdexcept>
#include <string>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QCoreApplication>
#include <QEventLoop>
#include <QObject>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include <QDebug>
#include "http_poster.hh"
#include "logging.hh"
#include "qt_utility.hh"

using std::string;

// File qtbase/src/network/access/qhttpthreaddelegate.cpp
// static QNetworkReply::NetworkError statusCodeFromHttp(int httpStatusCode, const QUrl &url)
// http://code.qt.io/cgit/qt/qtbase.git/tree/src/network/access/qhttpthreaddelegate.cpp?h=dev

string QtHttpPoster::request(const string url, const string payload) {
    QEventLoop waitLoop;

    QUrl endpoint(QString::fromStdString(url));

    spdlog::info("url is {}", url);
    spdlog::info("payload is {}", payload);

    QNetworkAccessManager manager;
    QNetworkRequest request(endpoint);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QByteArray authorizationValue("token ");
    authorizationValue.append(QString::fromStdString(tokenStore->getToken()));

    request.setRawHeader(QByteArray("Authorization"), authorizationValue);

    QByteArray content =  QString::fromStdString(payload).toUtf8();
    QNetworkReply* reply = manager.post(request, content);

    QObject::connect(reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit);
    waitLoop.exec();

    QByteArray result = reply->readAll();
    qt_utility::handleHttpError("HTTP POST:", reply, result);

    return QString(result).toStdString();
}
