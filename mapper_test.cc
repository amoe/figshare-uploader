#include <gmock/gmock.h>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

using ::testing::Eq;

class ArticleCreationRequest {
public:
    ArticleCreationRequest(std::string title) : title(title) { }
    std::string toJson();
private:
    std::string title;
};

std::string ArticleCreationRequest::toJson() {
    QJsonObject object;
    QJsonValue titleVal(QString::fromStdString(this->title));

    object.insert("title", titleVal);

    QString result = QString::fromUtf8(QJsonDocument(object).toJson());

    return result.toStdString();
}

QJsonObject deserialize(std::string input) {
    auto result = QJsonDocument::fromJson(QString::fromStdString(input).toUtf8());
    return result.object();
}


TEST(ArticleCreationRequestTest, SerializesToJson) {
    ArticleCreationRequest request("To Serve Man");
    
    std::string serializedResult = request.toJson();
        
    std::string expectedResult = "{\"title\": \"To Serve Man\"}";

    ASSERT_THAT(deserialize(serializedResult), Eq(deserialize(expectedResult)));
}

