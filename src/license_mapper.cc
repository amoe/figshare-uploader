#include <QDebug>
#include "license_mapper.hh"

LicenseMapper::LicenseMapper(HttpGetter* getter) : getter(getter) {
}

LicenseMapper::LicenseMapper(string jsonInput) {
    setFromJson(jsonInput);
}

void LicenseMapper::initializeLookup() {
    string result = getter->request("https://api.figshare.com/v2/licenses");
    setFromJson(result);
}

int LicenseMapper::mapName(const string name) {
    if (lookup.empty()) {
        initializeLookup();
    }

    auto it = lookup.find(name);
    if (it == lookup.end()) {
        throw std::runtime_error("license name not found");
    } else {
        return it->second;
    }

}

void LicenseMapper::setFromJson(string jsonInput) {
    lookup.clear();

    QJsonDocument document = QJsonDocument::fromJson(
        QString::fromStdString(jsonInput).toUtf8()
    );

    QJsonArray theArray = document.array();

    for (const QJsonValue& item : theArray) {
        QJsonObject license = item.toObject();
     
        string name = license.value("name").toString().toStdString();
        int value = license.value("value").toInt();
        
        lookup.insert({name, value});
    }

    qDebug() << "initialized with table size" << lookup.size();
}
