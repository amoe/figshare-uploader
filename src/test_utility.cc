#include <string>
#include <stdexcept>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QDebug>

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
        qDebug() << possibleError.errorString();
        throw new std::runtime_error(possibleError.errorString().toStdString());
    }
}


std::string currentDirectory() {
    QString result = QDir::currentPath();
    return result.toStdString();
}
