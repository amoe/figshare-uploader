#include <string>
#include <vector>
#include "optional.hpp"
#include "article_types.hh"
#include "requests.hh"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

using std::string;

string UploadCreationRequest::toJson() const {
    QJsonObject object;

    
    object.insert("name", QJsonValue(QString::fromStdString(name)));
    object.insert("md5", QJsonValue(QString::fromStdString(md5)));
    object.insert("size", QJsonValue((qint64) size));


    QString result = QString::fromUtf8(QJsonDocument(object).toJson());
    return result.toStdString();
}
