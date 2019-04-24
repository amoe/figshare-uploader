#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#include "http_getter.hh"
#include "group_mapper.hh"

using std::runtime_error;
using std::ostringstream;
using std::cout;
using std::endl;

// Note that the GroupMapper and the CategoryMapper share nearly identical
// implementations, except one uses a manual stub and one uses a gmock-created
// mock for testing.

GroupMapperImpl::GroupMapperImpl(HttpGetter* httpGetter) : httpGetter(httpGetter) {
    // Nothing to do here, we initialize lazily, because the token store might
    // not be intialized at this time.
}

void GroupMapperImpl::initializeGroups() {

    cout << "initializing group data from figshare api" << endl;

    ostringstream stringStream;
    stringStream << "https://api.figshare.com/v2"
                 << "/account/institution/groups";
    
    string result = httpGetter->request(stringStream.str());
    cout << "group response was " << result;

    auto document = QJsonDocument::fromJson(QString::fromStdString(result).toUtf8());
    
    if (!document.isArray()) {
        throw std::runtime_error("group response was formatted unexpectedly");
    }

    QJsonArray groupArray = document.array();

    for (const QJsonValue& item : groupArray) {
        QJsonObject group = item.toObject();
        
        string title = group.value("name").toString().toStdString();
        int id = group.value("id").toInt();
        
        lookup.insert({title, id});
    }

    std::cout << "initialized group data" << std::endl;

}

int GroupMapperImpl::getGroupIdByName(string groupName) {
    if (lookup.empty()) {
        initializeGroups();
    }

    auto it = lookup.find(groupName);
    if (it == lookup.end()) {
        throw runtime_error("group title not found");
    } else {
        return it->second;
    }
}


