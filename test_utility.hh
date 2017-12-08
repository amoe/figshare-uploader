#include <string>
#include <QJsonObject>

using std::string;

QJsonObject deserialize(const std::string input);
string fetchString(
    const string textRepresentation, const string key
);
