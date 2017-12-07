#include <gmock/gmock.h>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include "raw_literals.hh"

using std::string;
using std::map;
using ::testing::Eq;

class LicenseMapper {
public:
    LicenseMapper(string jsonInput);
    int mapName(string name);
    
private:
    map<string, int> lookup;
};


LicenseMapper::LicenseMapper(string jsonInput) {
    QJsonDocument document = QJsonDocument::fromJson(
        QString::fromStdString(jsonInput).toUtf8()
    );

    QJsonArray theArray = document.array();

    for (const QJsonValue& item : theArray) {
        QJsonObject category = item.toObject();
        
        string name = category.value("name").toString().toStdString();
        int value = category.value("value").toInt();
        
        lookup.insert({name, value});
    }

    // now finished
}

int LicenseMapper::mapName(const string name) {
    return lookup[name];
}


TEST(LicenseMapper, MapsLicenseSuccessfully) {
    LicenseMapper mapper(raw_literals::licensesResponse);
    int licenseId = mapper.mapName("CC BY 4.0");

    ASSERT_THAT(licenseId, Eq(1));
}
