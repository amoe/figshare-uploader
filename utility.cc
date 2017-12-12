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

bool containsKey(const string input, const string key) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    const auto qKey = QString::fromStdString(key);
    
    return result.object().contains(qKey);
}

static vector<string> splitByRegexp(const string input, const string regexp) {
    auto qInput = QString::fromStdString(input);

    QRegExp separator(QString::fromStdString(regexp));

    QStringList items = qInput.split(separator);
    
    vector<string> results;
    for (auto item : items) {
        results.push_back(item.toStdString());
    }

    return results;
}

vector<string> splitCommas(const string input) {
    return splitByRegexp(input, ",\\s*");
}

vector<string> splitSpaces(const string input) {
    return splitByRegexp(input, "\\s+");
}

