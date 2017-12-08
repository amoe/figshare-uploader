#include <string>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

using std::string;

QJsonObject deserialize(const std::string input) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    return result.object();
}

string fetchString(
    const string input, const string key
) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    const auto qKey = QString::fromStdString(key);
    
    return result.object().value(qKey).toString().toStdString();
}
