#ifndef ARTICLE_MAPPER_HH
#define ARTICLE_MAPPER_HH

#include <string>
#include <vector>
#include <QJsonValue>
#include "article_type_mapper.hh"
#include "requests.hh"
#include "category_mapper.hh"

class ArticleMapper {
public:
    ArticleMapper(ArticleTypeMapper typeMapper, CategoryMapper categoryMapper)
        : typeMapper(typeMapper), categoryMapper(categoryMapper) { }

    ArticleCreationRequest mapFromExcel(const vector<string> excelRow);
    string mapToFigshare(ArticleCreationRequest request);
    
private:
    ArticleTypeMapper typeMapper;
    CategoryMapper categoryMapper;

    // ???
    QJsonValue mapType(ArticleType type);
};

#endif // ARTICLE_MAPPER_HH
