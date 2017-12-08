#ifndef ARTICLE_MAPPER_HH
#define ARTICLE_MAPPER_HH

#include <string>
#include <vector>
#include <QJsonValue>
#include "article_type_mapper.hh"

class ArticleMapper {
public:
    ArticleMapper(ArticleTypeMapper typeMapper) : typeMapper(typeMapper) { }

    ArticleCreationRequest mapFromExcel(const vector<string> excelRow);
    string mapToFigshare(ArticleCreationRequest request);
    
private:
    ArticleTypeMapper typeMapper;

    // ???
    QJsonValue mapType(ArticleType type);
};

#endif // ARTICLE_MAPPER_HH
