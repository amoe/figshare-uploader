#include <iostream>
#include <string>
#include <exception>
#include "http_getter.hh"
#include "group_mapper.hh"
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

using std::runtime_error;


GroupMapperImpl::GroupMapperImpl(HttpGetter* httpGetter) : httpGetter(httpGetter) {
    std::ostringstream stringStream;
    stringStream << "https://api.figshare.com/v2"
                 << "/account/institution/groups";
    
    string result = httpGetter->request(stringStream.str());

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
}

int GroupMapperImpl::getGroupIdByName(string groupName) {
    auto it = lookup.find(groupName);
    if (it == lookup.end()) {
        throw std::runtime_error("category title not found");
    } else {
        return it->second;
    }
}


