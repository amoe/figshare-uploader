#include <map>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include "ext/optional.hpp"
#include "requests.hh"
#include "article_types.hh"
#include "article_type_mapper.hh"
#include "article_mapper.hh"

using nonstd::optional;
using nonstd::nullopt;
using std::vector;
using std::string;
using std::map;


string ArticleMapper::mapToFigshare(const ArticleCreationRequest request) {
    QJsonObject object;
    QJsonValue titleVal(QString::fromStdString(request.getTitle()));
    QJsonValue descriptionVal(QString::fromStdString(request.getDescription()));
    QJsonValue licenseVal(request.getLicense());

    QJsonValue fundingVal;
    if (request.getFunding()) {
        fundingVal = QJsonValue(QString::fromStdString(request.getFunding().value()));
    } else {
        fundingVal = QJsonValue(QJsonValue::Null);
    }
    
    QJsonArray keywordsVal;

    for (string s : request.getKeywords()) {
        QJsonValue thisTag(QString::fromStdString(s));
        keywordsVal.push_back(thisTag);
    }

    QJsonArray referencesVal;
    for (string s : request.getReferences()) {
        QJsonValue thisReference(QString::fromStdString(s));
        referencesVal.push_back(thisReference);
    }

    QJsonArray categoriesVal;
    for (int c : request.getCategories()) {
        QJsonValue thisCategoryId(c);
        categoriesVal.push_back(thisCategoryId);
    }

    // Note that authors has special handling here.
    QJsonArray authorsVal;
    for (string a : request.getAuthors()) {
        QJsonObject authorObject;
        QJsonValue authorName(QString::fromStdString(a));
        
        authorObject.insert("name", authorName);
        authorsVal.push_back(authorObject);
    }

    object.insert("license", licenseVal);
    object.insert("defined_type", mapType(request.getArticleType()));
    object.insert("funding", fundingVal);
    object.insert("authors", authorsVal);
    object.insert("references", referencesVal);
    object.insert("keywords", keywordsVal);
    object.insert("title", titleVal);
    object.insert("description", descriptionVal);
    object.insert("categories", categoriesVal);

    QString result = QString::fromUtf8(QJsonDocument(object).toJson());

    return result.toStdString();
}

QJsonValue ArticleMapper::mapType(ArticleType type) {
    return QJsonValue(
        QString::fromStdString(typeMapper.toFigshare(type))
    );
}

ArticleCreationRequest ArticleMapper::mapFromExcel(const vector<string> excelRow) {
    string title = excelRow.at(0);
    string description = excelRow.at(5);
    vector<string> keywords = excelRow.at(4);
    vector<string> references = excelRow.at(6);
    vector<int> categories = excelRow.at(2);
    vector<string> authors = excelRow.at(1);

    optional<string> funding = optional<string>("Some funding");

    ArticleType articleType = ArticleType::CODE;
    int license = 1;
    
    ArticleCreationRequest result(
        title, description, keywords, references, categories, authors,
        funding, articleType, license
    );

    // This will use the copy constructor for ArticleCreationRequest.
    return result;
}
