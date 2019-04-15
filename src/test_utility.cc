#include <string>
#include <stdexcept>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>

using std::string;

QJsonObject deserialize(const std::string input) {
    QJsonParseError possibleError;
    auto result = QJsonDocument::fromJson(
        QString::fromStdString(input).toUtf8(),
        &possibleError
    );

    if (possibleError.error == QJsonParseError::NoError) {
        return result.object();
    } else {
        throw new std::runtime_error("parse error");
    }
}


std::string currentDirectory() {
    QString result = QDir::currentPath();
    return result.toStdString();
}
