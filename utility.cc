#include <string>
#include <vector>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>

using std::string;
using std::vector;

// XXX duplicates code from test utilities.  ??
string fetchString(
    const string input, const string key
) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    const auto qKey = QString::fromStdString(key);
    
    return result.object().value(qKey).toString().toStdString();
}

vector<string> splitCommas(const string input) {
    auto qInput = QString::fromStdString(input);
    QRegExp separator(",\\s*");
    QStringList items = qInput.split(separator);
    

    vector<string> results;
    for (auto item : items) {
        results.push_back(item.toStdString());
    }

    return results;
}
