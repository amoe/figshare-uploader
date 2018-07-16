#include <map>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include "optional.hpp"
#include "requests.hh"
#include "article_types.hh"
#include "article_type_mapper.hh"
#include "article_mapper.hh"
#include "utility.hh"
#include "column_mapping.hh"

using nonstd::optional;
using nonstd::nullopt;
using std::vector;
using std::string;
using std::map;


ArticleCreationRequest ArticleMapperImpl::mapFromExcel(const vector<string> excelRow) {
    string title = excelRow.at(0);
    string description = excelRow.at(5);

    vector<string> keywords = splitCommas(excelRow.at(4));

    // We only support one reference at the moment!
    vector<string> references;
    string referencesSheetVal = excelRow.at(column_mapping::REFERENCES);

    if (!referencesSheetVal.empty()) 
        references.push_back(referencesSheetVal);

    vector<int> categories;
    string categoryTitle = excelRow.at(2);

    if (!categoryTitle.empty())
        categories.push_back(categoryMapper.mapTitle(categoryTitle));
    
    vector<string> authors = splitCommas(excelRow.at(1));

    string rawFunding = excelRow.at(7);
    optional<string> funding;

    // XXX: whitespace only is not handled here
    if (rawFunding.empty()) {
        funding = nullopt;
    } else {
        funding = optional<string>(rawFunding);
    }

    ArticleType articleType = typeMapper.mapFromString(excelRow.at(3));

    int license = 1;

    string identifierSheetVal = excelRow.at(column_mapping::IDENTIFIER);

    map<string, string> customFields = customFieldMapper.mapCustomFields(excelRow);
    
    ArticleCreationRequest result(
        title, description, keywords, references, categories, authors,
        funding, articleType, license, identifierSheetVal, customFields
    );

    // This will use the copy constructor for ArticleCreationRequest.
    return result;
}

string ArticleMapperImpl::mapToFigshare(const ArticleCreationRequest request) {
    QJsonObject object;
    QJsonValue titleVal(QString::fromStdString(request.title));
    QJsonValue descriptionVal(QString::fromStdString(request.description));
    QJsonValue licenseVal(request.license);

    // Not really clear if this should be mapped at all.
    QJsonValue fundingVal;

    if (request.funding) {
        fundingVal = QJsonValue(QString::fromStdString(request.funding.value()));
        object.insert("funding", fundingVal);
    } else {
        // Do nothing!
    }
    
    QJsonArray keywordsVal;

    for (string s : request.keywords) {
        QJsonValue thisTag(QString::fromStdString(s));
        keywordsVal.push_back(thisTag);
    }

    QJsonArray referencesVal;
    for (string s : request.references) {
        QJsonValue thisReference(QString::fromStdString(s));
        referencesVal.push_back(thisReference);
    }

    QJsonArray categoriesVal;
    for (int c : request.categories) {
        QJsonValue thisCategoryId(c);
        categoriesVal.push_back(thisCategoryId);
    }

    // Note that authors has special handling here.
    QJsonArray authorsVal;
    for (string a : request.authors) {
        QJsonObject authorObject;
        QJsonValue authorName(QString::fromStdString(a));
        
        authorObject.insert("name", authorName);
        authorsVal.push_back(authorObject);
    }

    object.insert("license", licenseVal);
    object.insert("defined_type", mapType(request.articleType));
    object.insert("authors", authorsVal);
    object.insert("references", referencesVal);
    object.insert("keywords", keywordsVal);
    object.insert("title", titleVal);
    object.insert("description", descriptionVal);
    object.insert("categories", categoriesVal);

    QString result = QString::fromUtf8(QJsonDocument(object).toJson());

    return result.toStdString();
}

QJsonValue ArticleMapperImpl::mapType(ArticleType type) {
    return QJsonValue(
        QString::fromStdString(typeMapper.toFigshare(type))
    );
}
