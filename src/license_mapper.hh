#ifndef LICENSE_MAPPER_HH
#define LICENSE_MAPPER_HH

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <string>
#include <map>
#include "http_getter.hh"

using std::string;
using std::map;

class LicenseMapper {
public:
    LicenseMapper(string jsonInput);
    LicenseMapper(HttpGetter* getter);

    int mapName(string name);
    void setFromJson(string jsonInput);
    
private:
    void initializeLookup();
    map<string, int> lookup;
    HttpGetter* getter;
};

#endif /* LICENSE_MAPPER_HH */
