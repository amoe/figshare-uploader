#include <string>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

using std::string;

// XXX duplicates code from test utilities.  ??
string fetchString(
    const string input, const string key
) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    const auto qKey = QString::fromStdString(key);
    
    return result.object().value(qKey).toString().toStdString();
}
