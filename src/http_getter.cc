#include <QNetworkAccessManager>
#include <QUrl>
#include <QCoreApplication>
#include <QEventLoop>
#include <QObject>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
#include "http_getter.hh"
#include "qt_utility.hh"

using std::string;

string QtHttpGetter::request(const string url) {
    QEventLoop waitLoop;

    QUrl endpoint(QString::fromStdString(url));

    QNetworkAccessManager manager;

    QNetworkRequest request(endpoint);
    QByteArray authorizationValue("token ");
    authorizationValue.append(QString::fromStdString(tokenStore->getToken()));
    request.setRawHeader(QByteArray("Authorization"), authorizationValue);

    QNetworkReply* reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, &waitLoop, &QEventLoop::quit);
    waitLoop.exec();
    QByteArray result = reply->readAll();

    qt_utility::handleHttpError("HTTP GET:", reply, result);

    return QString(result).toStdString();
}
