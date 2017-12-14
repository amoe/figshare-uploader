#include "file_info.hh"

#include <QJsonDocument>
#include <QJsonObject>

FileInfo FileInfo::fromJson(string jsonText) {
    std::string uploadContainerUrl;
    std::string fileName;
    int64_t id;

    QJsonDocument result = QJsonDocument::fromJson(
        QString::fromStdString(jsonText).toUtf8()
    );
    QJsonObject object = result.object();
    
    uploadContainerUrl = object.value("upload_url").toString().toStdString();
    fileName = object.value("name").toString().toStdString();
    id = object.value("id").toInt();
    
    return FileInfo(uploadContainerUrl, fileName, id);
}
