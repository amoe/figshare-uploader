#include <string>
#include <stdexcept>
#include <map>
#include <QJsonDocument>
#include <QString>
#include <QJsonObject>
#include "upload_container_info.hh"

using std::string;
using std::map;

UploadContainerInfo UploadContainerInfo::fromJson(string jsonText) {
    string name;
    int64_t size;
    string md5;
    string token;
    UploadContainerStatus status;
    vector<FilePart> parts;

    QJsonDocument result = QJsonDocument::fromJson(
        QString::fromStdString(jsonText).toUtf8()
    );
    QJsonObject object = result.object();

    name = object.value("name").toString().toStdString();
    size = object.value("size").toInt();   // Does this lose precision?
    md5 = object.value("md5").toString().toStdString();
    token = object.value("token").toString().toStdString();
    status = mapStatus(object.value("status").toString().toStdString());
    parts = mapParts(object.value("parts").toArray());

    return UploadContainerInfo(name, size, md5, token, status, parts);
}

vector<FilePart> UploadContainerInfo::mapParts(QJsonArray partsArray) {
    std::vector<FilePart> allParts;

    // Not so clear why this needs to be const, but it does.
    for (const auto& partValue : partsArray) {
        QJsonObject partObject = partValue.toObject();
        FilePart thePart = FilePart::fromJson(partObject);
        allParts.push_back(thePart);
    }

    return allParts;
}

UploadContainerStatus UploadContainerInfo::mapStatus(string status) {
    map<string, UploadContainerStatus> statuses = {
        {"PENDING", UploadContainerStatus::PENDING},
        {"COMPLETED", UploadContainerStatus::COMPLETED},
        {"ABORTED", UploadContainerStatus::ABORTED}
    };

    auto it = statuses.find(status);
    if (it == statuses.end()) {
        throw std::runtime_error("upload container status not found");
    } else {
        return it->second;
    }
}
