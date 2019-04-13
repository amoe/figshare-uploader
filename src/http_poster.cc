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
#include <iostream>
#include "http_poster.hh"
#include "logging.hh"

using std::string;

// File qtbase/src/network/access/qhttpthreaddelegate.cpp
// static QNetworkReply::NetworkError statusCodeFromHttp(int httpStatusCode, const QUrl &url)
// http://code.qt.io/cgit/qt/qtbase.git/tree/src/network/access/qhttpthreaddelegate.cpp?h=dev

string QtHttpPoster::request(const string url, const string payload) {
    QEventLoop waitLoop;

    QUrl endpoint(QString::fromStdString(url));

    qDebug() << "url is" << endpoint;
    std::cout << "payload is" << payload;

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

    auto error = reply->error();
    qDebug() << error;
    qDebug() << result;
    if (error != QNetworkReply::NoError) {
        qDebug() << result;
        QString errorMessage = QString::fromUtf8(result);
        string message = "HTTP POST: " + errorMessage.toStdString();
        throw std::runtime_error(message);
    }


    return QString(result).toStdString();
}
