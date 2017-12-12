#include <string>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

using std::string;

QJsonObject deserialize(const std::string input) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    return result.object();
}


std::string currentDirectory() {
    QString result = QDir::currentPath();
    return result.toStdString();
}
