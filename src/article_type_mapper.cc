#include <iostream>
#include <map>
#include "article_types.hh"
#include "article_type_mapper.hh"

using std::string;
using std::map;

ArticleTypeMapper::ArticleTypeMapper() {
    articleTypeFriendlyNames.insert({"Figure", ArticleType::FIGURE});
    articleTypeFigshareNames.insert({ArticleType::FIGURE, "figure"});
}

ArticleType ArticleTypeMapper::mapFromString(const string input) {
    return articleTypeFriendlyNames[input];
}

string ArticleTypeMapper::toFigshare(ArticleType input) {
    return articleTypeFigshareNames[input];
}
