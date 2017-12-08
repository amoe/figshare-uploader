#include <string>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

using std::string;

QJsonObject deserialize(const std::string input) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    return result.object();
}

