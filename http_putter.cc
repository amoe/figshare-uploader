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

using std::string;

// Basically a clone of the poster code.   

// File qtbase/src/network/access/qhttpthreaddelegate.cpp
// static QNetworkReply::NetworkError statusCodeFromHttp(int httpStatusCode, const QUrl &url)
// http://code.qt.io/cgit/qt/qtbase.git/tree/src/network/access/qhttpthreaddelegate.cpp?h=dev

string QtHttpPutter::request(const string url, const string payload) {
    qDebug() << "payload size in putter is " << payload.size();
    
    QEventLoop waitLoop;
    QUrl endpoint(QString::fromStdString(url));

    QNetworkAccessManager manager;
    QNetworkRequest request(endpoint);
    

    // XXX: differs from poster
    // request.setHeader(
    //     QNetworkRequest::ContentTypeHeader, "application/octet-stream"
    // );


    QByteArray authorizationValue("token ");
    authorizationValue.append(QString::fromStdString(token));

    // request.setRawHeader(QByteArray("Authorization"), authorizationValue);

    QByteArray content =  QString::fromStdString(payload).toUtf8();
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
