#ifndef ARTICLE_TYPE_MAPPER_HH
#define ARTICLE_TYPE_MAPPER_HH

#include <string>
#include <map>
#include "article_types.hh"

using std::string;
using std::map;

class ArticleTypeMapper {
public:
    ArticleTypeMapper();
    ArticleType mapFromString(const string input);
    string toFigshare(ArticleType input);
private:
    map<string, ArticleType> articleTypeFriendlyNames;
    map<ArticleType, string> articleTypeFigshareNames;
};

#endif // ARTICLE_TYPE_MAPPER_HH
