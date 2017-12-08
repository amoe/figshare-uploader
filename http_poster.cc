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
#include "http_poster.hh"

using std::string;

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
