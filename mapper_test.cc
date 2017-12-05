#include <gmock/gmock.h>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

using ::testing::Eq;


class ArticleCreationRequest {
public:
    ArticleCreationRequest(std::string title) : title(title) { }
    std::string toJson();
    std::string getTitle();
private:
    std::string title;
};

std::string ArticleCreationRequest::getTitle() {
    return this->title;
}

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

class ArticleMapper {
public:
    ArticleMapper() { }

    ArticleCreationRequest map(const std::vector<std::string> excelRow);
};

ArticleCreationRequest ArticleMapper::map(const std::vector<std::string> excelRow) {
    std::string title = excelRow.at(0);
    ArticleCreationRequest result(title);

    // This will use the copy constructor for ArticleCreationRequest.
    return result;
}



TEST(ArticleMapperTest, CorrectlyMapsRow) {
    ArticleMapper myMapper;
    std::vector<std::string> row;
    row.push_back("To Serve Man");

    ArticleCreationRequest request = myMapper.map(row);

    ASSERT_THAT(request.getTitle(), Eq("To Serve Man"));
}


TEST(ArticleCreationRequestTest, SerializesToJson) {
    ArticleCreationRequest request("To Serve Man");
    
    std::string serializedResult = request.toJson();
        
    std::string expectedResult = "{\"title\": \"To Serve Man\"}";

    ASSERT_THAT(deserialize(serializedResult), Eq(deserialize(expectedResult)));
}

