#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include "category_mapper.hh"
#include <QDebug>

using std::string;

CategoryMapper::CategoryMapper(string jsonInput) {
    setFromJson(jsonInput);
}

int CategoryMapper::mapTitle(const string title) {
    auto it = lookup.find(title);
    if (it == lookup.end()) {
        throw std::runtime_error("category title not found");
    } else {
        return it->second;
    }
}

void CategoryMapper::setFromJson(string jsonInput) {
    lookup.clear();

    QJsonDocument document = QJsonDocument::fromJson(
        QString::fromStdString(jsonInput).toUtf8()
    );

    QJsonArray theArray = document.array();

    for (const QJsonValue& item : theArray) {
        QJsonObject category = item.toObject();
        
        string title = category.value("title").toString().toStdString();
        int id = category.value("id").toInt();
        
        lookup.insert({title, id});
    }

    qDebug() << "initialized with table size" << lookup.size();
}
