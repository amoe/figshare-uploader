#include <gmock/gmock.h>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "test_utility.hh"
#include "raw_literals.hh"

using ::testing::Eq;
using ::testing::StartsWith;
using ::testing::EndsWith;

using std::vector;
using std::string;

class ArticleCreationRequest {
public:
    ArticleCreationRequest(
        string title, string description,
        vector<string> keywords,
        vector<string> references,
        vector<int> categories,
        vector<string> authors
    ) : title(title), description(description), keywords(keywords),
        references(references), categories(categories),  authors(authors)
        { }
    string toJson();
    string getTitle();
    string getDescription();
    vector<string> getKeywords();
    vector<string> getReferences() const;
    vector<int> getCategories() const;
    vector<string> getAuthors() const;
private:
    string title;
    string description;
    vector<string> keywords;
    vector<string> references;
    vector<int> categories;
    vector<string> authors;
};

vector<string> ArticleCreationRequest::getAuthors() const {
    return this->authors;
}

string ArticleCreationRequest::getTitle() {
    return this->title;
}

string ArticleCreationRequest::getDescription() {
    return this->description;
}

vector<string> ArticleCreationRequest::getKeywords() {
    return this->keywords;
}

vector<string> ArticleCreationRequest::getReferences() const {
    return this->references;
}

vector<int> ArticleCreationRequest::getCategories() const {
    return this->categories;
}


string ArticleCreationRequest::toJson() {
    QJsonObject object;
    QJsonValue titleVal(QString::fromStdString(this->title));
    QJsonValue descriptionVal(QString::fromStdString(this->description));

    QJsonArray keywordsVal;

    for (string s : keywords) {
        QJsonValue thisTag(QString::fromStdString(s));
        keywordsVal.push_back(thisTag);
    }

    QJsonArray referencesVal;
    for (string s : references) {
        QJsonValue thisReference(QString::fromStdString(s));
        referencesVal.push_back(thisReference);
    }

    QJsonArray categoriesVal;
    for (int c : categories) {
        QJsonValue thisCategoryId(c);
        categoriesVal.push_back(thisCategoryId);
    }

    QJsonArray authorsVal;
    for (string a : authors) {
        QJsonObject authorObject;
        QJsonValue authorName(QString::fromStdString(a));
        
        authorObject.insert("name", authorName);
        authorsVal.push_back(authorObject);
    }

    object.insert("authors", authorsVal);
    object.insert("references", referencesVal);
    object.insert("keywords", keywordsVal);
    object.insert("title", titleVal);
    object.insert("description", descriptionVal);
    object.insert("categories", categoriesVal);

    QString result = QString::fromUtf8(QJsonDocument(object).toJson());

    return result.toStdString();
}

class ArticleMapper {
public:
    ArticleMapper() { }

    ArticleCreationRequest map(const vector<string> excelRow);
};

ArticleCreationRequest ArticleMapper::map(const vector<string> excelRow) {
    string title = excelRow.at(0);
    string description = excelRow.at(5);
    vector<string> keywords;
    vector<string> references;
    vector<int> categories;
    vector<string> authors;

    ArticleCreationRequest result(
        title, description, keywords, references, categories, authors
    );

    // This will use the copy constructor for ArticleCreationRequest.
    return result;
}



TEST(ArticleMapperTest, CorrectlyMapsRow) {
    ArticleMapper myMapper;
    vector<string> row;
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
    vector<string> keywords;
    keywords.push_back("Bethlehem");
    keywords.push_back("Crafts");

    vector<string> references;
    references.push_back("https://www.loc.gov/item/mpc2004001373/PP/");

    vector<int> categories;
    categories.push_back(1703);

    vector<string> authors;
    authors.push_back("Freja Howat-Maxted");

    ArticleCreationRequest request(
        "To Serve Man",
        "Some description",
        keywords,
        references,
        categories,
        authors
    );
    
    string serializedResult = request.toJson();

    std::cout << serializedResult << std::endl;

    ASSERT_THAT(
        deserialize(serializedResult),
        Eq(deserialize(raw_literals::expectedResult))
    );
}


