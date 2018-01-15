#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "responses.hh"

ArticleGetResponse ArticleGetResponse::fromJson(string jsonText) {
    int id;

    qDebug() << QString::fromStdString(jsonText);

    QJsonDocument result = QJsonDocument::fromJson(
        QString::fromStdString(jsonText).toUtf8()
    );
    QJsonObject object = result.object();
    
    id = object.value("id").toInt();
    
    return ArticleGetResponse(id);
}

