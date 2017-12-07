#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

QJsonObject deserialize(const std::string input) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    return result.object();
}
