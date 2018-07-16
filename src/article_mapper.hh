#ifndef ARTICLE_MAPPER_HH
#define ARTICLE_MAPPER_HH

#include <string>
#include <vector>
#include <QJsonValue>
#include <gmock/gmock.h>
#include "article_type_mapper.hh"
#include "requests.hh"
#include "category_mapper.hh"
#include "custom_field_mapper.hh"

class ArticleMapper {
public:
    virtual ArticleCreationRequest mapFromExcel(const vector<string> excelRow)
    = 0;
    virtual string mapToFigshare(ArticleCreationRequest request) = 0;
};


class ArticleMapperImpl : public ArticleMapper {
public:
    ArticleMapperImpl(
        ArticleTypeMapper typeMapper,
        CategoryMapper categoryMapper,
        CustomFieldMapper customFieldMapper
    ) : typeMapper(typeMapper), 
        categoryMapper(categoryMapper),
        customFieldMapper(customFieldMapper) { }

    ArticleCreationRequest mapFromExcel(const vector<string> excelRow);
    string mapToFigshare(ArticleCreationRequest request);
    
private:
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper;
    CustomFieldMapper customFieldMapper;

    // ???
    QJsonValue mapType(ArticleType type);
};

class MockArticleMapper : public ArticleMapper {
public:
    MOCK_METHOD1(mapFromExcel, ArticleCreationRequest(const vector<string> excelRow));
    MOCK_METHOD1(mapToFigshare, string(ArticleCreationRequest request));
};

#endif // ARTICLE_MAPPER_HH
