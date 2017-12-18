#include <iostream>
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
#include "http_putter.hh"
#include "logging.hh"

using std::string;

// Basically a clone of the poster code.   

// File qtbase/src/network/access/qhttpthreaddelegate.cpp
// static QNetworkReply::NetworkError statusCodeFromHttp(int httpStatusCode, const QUrl &url)
// http://code.qt.io/cgit/qt/qtbase.git/tree/src/network/access/qhttpthreaddelegate.cpp?h=dev

string QtHttpPutter::request(const string url, const string payload) {
    debugf("payload size in putter is %d", payload.size());
    
    QEventLoop waitLoop;
    QUrl endpoint(QString::fromStdString(url));

    QNetworkAccessManager manager;
    QNetworkRequest request(endpoint);
    

    // XXX: differs from poster
    // request.setHeader(
    //     QNetworkRequest::ContentTypeHeader, "application/octet-stream"
    // );


    QByteArray authorizationValue("token ");
    authorizationValue.append(QString::fromStdString(tokenStore->getToken()));

    // request.setRawHeader(QByteArray("Authorization"), authorizationValue);

    // !!!
    // Note that in the other HTTP access classes, we are deserializing payload
    // from UTF-8, because it is string data.  We can NOT do this here, because
    // this must be posted as binary.

    // If you create this byte array using a QString function, it will result in
    // MD5 failures on the server end, leading to a file status of `ic_failure`,
    // because while std::string is just a sequence of bytes, QString is another
    // beast entirely.

    // This function is in Qt core, as QByteArray::fromStdString (since 5.4).
    // However, we need to support Qt 5.2 due to the Trusty CI server.
    QByteArray content(payload.data(), int(payload.size()));

    debugf("content size just before sending is %d", content.size());

    QNetworkReply* reply = manager.put(request, content);

    QObject::connect(reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit);
    waitLoop.exec();

    QByteArray result = reply->readAll();

    auto error = reply->error();
    if (error != QNetworkReply::NoError && error != QNetworkReply::RemoteHostClosedError) {
        qDebug() << error;
        qDebug() << reply->errorString();
        qDebug() << result;
        throw std::runtime_error(
            "something went wrong in the network request"
        );
    }

    return QString(result).toStdString();
}
