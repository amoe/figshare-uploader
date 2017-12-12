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

using std::string;

// File qtbase/src/network/access/qhttpthreaddelegate.cpp
// static QNetworkReply::NetworkError statusCodeFromHttp(int httpStatusCode, const QUrl &url)
// http://code.qt.io/cgit/qt/qtbase.git/tree/src/network/access/qhttpthreaddelegate.cpp?h=dev

string QtHttpPoster::request(const string url, const string payload) {
    QEventLoop waitLoop;

    QUrl endpoint(QString::fromStdString(url));

    QNetworkAccessManager manager;
    QNetworkRequest request(endpoint);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QByteArray authorizationValue("token ");
    authorizationValue.append(QString::fromStdString(token));

    request.setRawHeader(QByteArray("Authorization"), authorizationValue);

    QByteArray content =  QString::fromStdString(payload).toUtf8();
    QNetworkReply* reply = manager.post(request, content);

    QObject::connect(reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit);
    waitLoop.exec();

    QByteArray result = reply->readAll();

    auto error = reply->error();
    if (error != QNetworkReply::NoError) {
        qDebug() << result;
        throw std::runtime_error(
            "something went wrong in the network request"
        );
    }


    return QString(result).toStdString();
}
