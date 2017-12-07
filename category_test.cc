#include <gmock/gmock.h>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include "raw_literals.hh"

using std::string;
using std::map;
using ::testing::Eq;

class CategoryMapper {
public:
    CategoryMapper(string jsonInput);
    int mapTitle(string title);
    
private:
    map<string, int> lookup;
};


CategoryMapper::CategoryMapper(string jsonInput) {
    QJsonDocument document = QJsonDocument::fromJson(
        QString::fromStdString(jsonInput).toUtf8()
    );

    // For some reason the document is null again and I can't remember why.
    std::cout << document.isNull() << std::endl;

    QJsonArray theArray = document.array();

    for (const QJsonValue& item : theArray) {
        QJsonObject category = item.toObject();
        
        string title = category.value("title").toString().toStdString();
        int id = category.value("id").toInt();
        
        lookup.insert({title, id});
    }

    std::cout << lookup.size() << std::endl;
    // now finsihed.
}

int CategoryMapper::mapTitle(const string title) {
    return lookup[title];
}



TEST(MyComponent, ActsAsIExpect) {
    CategoryMapper mapper(raw_literals::categoryResponse);
    int categoryId = mapper.mapTitle("Middle Eastern and African History");

    ASSERT_THAT(categoryId, Eq(1703));
}

