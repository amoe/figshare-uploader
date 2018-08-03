#include <string>
#include <vector>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QDir>
#include <QJsonObject>
#include <QFileInfo>

using std::string;
using std::vector;

string resolvePath(string base, string relative) {
    // retrieve the dirname
    QString qPath = QString::fromStdString(base);
    QFileInfo fileInfo(qPath);
    QDir dirname = fileInfo.dir();

    // now join it to the leaf
    QString absolutePath = dirname.absoluteFilePath(
        QString::fromStdString(relative)
    );

    QString nativePath = QDir::toNativeSeparators(absolutePath);
    
    return nativePath.toStdString();
}

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

vector<string> splitSemicolons(const string input) {
    return splitByRegexp(input, "\\s*;\\s*");
}

vector<string> splitCommas(const string input) {
    return splitByRegexp(input, ",\\s*");
}

vector<string> splitSpaces(const string input) {
    return splitByRegexp(input, "\\s+");
}


string basename(string path) {
    QString qPath = QString::fromStdString(path);
    QFileInfo fileInfo(qPath);
    QString basename = fileInfo.fileName();
    return basename.toStdString();
}

bool isWhitespaceOnly(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isspace(input.at(i))) 
            return false;
    }

    return true;
}
