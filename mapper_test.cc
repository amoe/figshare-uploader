#include <gmock/gmock.h>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "raw_literals.hh"

using ::testing::Eq;
using ::testing::StartsWith;
using ::testing::EndsWith;

using std::vector;
using std::string;

class ArticleCreationRequest {
public:
    ArticleCreationRequest(
        std::string title, std::string description,
        std::vector<std::string> keywords,
        vector<string> references
    ) : title(title), description(description), keywords(keywords),
        references(references) { }
    std::string toJson();
    std::string getTitle();
    std::string getDescription();
    std::vector<std::string> getKeywords();
    vector<string> getReferences() const;
private:
    std::string title;
    std::string description;
    std::vector<std::string> keywords;
    vector<string> references;
};

std::string ArticleCreationRequest::getTitle() {
    return this->title;
}

std::string ArticleCreationRequest::getDescription() {
    return this->description;
}

std::vector<std::string> ArticleCreationRequest::getKeywords() {
    return this->keywords;
}

vector<string> ArticleCreationRequest::getReferences() const {
    return this->references;
}


std::string ArticleCreationRequest::toJson() {
    QJsonObject object;
    QJsonValue titleVal(QString::fromStdString(this->title));
    QJsonValue descriptionVal(QString::fromStdString(this->description));

    QJsonArray keywordsVal;

    for (std::string s : keywords) {
        QJsonValue thisTag(QString::fromStdString(s));
        keywordsVal.push_back(thisTag);
    }

    QJsonArray referencesVal;
    for (string s : references) {
        QJsonValue thisReference(QString::fromStdString(s));
        referencesVal.push_back(thisReference);
    }

    object.insert("references", referencesVal);
    object.insert("keywords", keywordsVal);
    object.insert("title", titleVal);
    object.insert("description", descriptionVal);

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
    std::string description = excelRow.at(5);
    std::vector<std::string> keywords;
    vector<string> references;

    ArticleCreationRequest result(title, description, keywords, references);

    // This will use the copy constructor for ArticleCreationRequest.
    return result;
}



TEST(ArticleMapperTest, CorrectlyMapsRow) {
    ArticleMapper myMapper;
    std::vector<std::string> row;
    row.push_back("To Serve Man");
    row.push_back("Freja Howat-Maxted");
    row.push_back("Middle Eastern and African Library");
    row.push_back("Figure");
    row.push_back("Bethlehem Crafts");
    row.push_back(R"(This is a digital reproduction of a black and white photographic print held in the Library of Congress.

Olive wood carving is an ancient tradition in Palestine that continues to the present day. It involves the skillful chiseling of olive wood and is most common in the Bethlehem region. The trade of olive wood ties in more broadly to the fact that the olive tree is symbolic for Palestinians; the olive tree is connected to the earth, they affirm Palestinian roots in the land.

Bethlehem merchants were already trading in locally produced religious devotional objects from olive wood and had identified their potential value in foreign markets from as early as the 1690s. However, it wan't until the late 19th, early 20th centuries that the material experienced a boom and played a part in the global circulation of Bethlehem's souvenir industry. Olive wood continues to be used in the production of souvenirs within the region today.

Taken in the early 20th century, the image exists as part of a wider series produced of traditional dress and people living in the area by G. Eric Matson.

This image exists as part of the Bethlehem Crafts collection in the Planet Bethlehem Archive.)");

    ArticleCreationRequest request = myMapper.map(row);

    ASSERT_THAT(request.getTitle(), Eq("To Serve Man"));
    ASSERT_THAT(request.getDescription(), StartsWith("This is a digital "));
    ASSERT_THAT(request.getDescription(), EndsWith("Planet Bethlehem Archive."));
}


TEST(ArticleCreationRequestTest, SerializesToJson) {
    std::vector<std::string> keywords;
    keywords.push_back("Bethlehem");
    keywords.push_back("Crafts");

    vector<string> references;
    references.push_back("https://www.loc.gov/item/mpc2004001373/PP/");

    ArticleCreationRequest request(
        "To Serve Man",
        "Some description",
        keywords,
        references
    );
    
    std::string serializedResult = request.toJson();

    std::cout << serializedResult << std::endl;

    ASSERT_THAT(
        deserialize(serializedResult),
        Eq(deserialize(raw_literals::expectedResult))
    );
}

