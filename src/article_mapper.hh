#ifndef ARTICLE_MAPPER_HH
#define ARTICLE_MAPPER_HH

#include <string>
#include <vector>
#include <QJsonValue>
#include "article_type_mapper.hh"
#include "requests.hh"
#include "category_mapper.hh"
#include "custom_field_mapper.hh"
#include "group_mapper.hh"

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
        CustomFieldMapper customFieldMapper,
        GroupMapper* groupMapper
    ) : typeMapper(typeMapper), 
        categoryMapper(categoryMapper),
        customFieldMapper(customFieldMapper),
        groupMapper(groupMapper) { }

    ArticleCreationRequest mapFromExcel(const vector<string> excelRow);
    string mapToFigshare(ArticleCreationRequest request);
    
private:
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper;
    CustomFieldMapper customFieldMapper;
    GroupMapper* groupMapper;

    // ???
    QJsonValue mapType(ArticleType type);
};


#endif // ARTICLE_MAPPER_HH
