#include <gmock/gmock.h>
#include "article_types.hh"

using ::testing::Eq;
using std::string;
using std::map;


class ArticleTypeMapper {
public:
    ArticleTypeMapper();
    ArticleType mapFromString(const string input);
private:
    map<string, ArticleType> articleTypeFriendlyNames;
};

ArticleTypeMapper::ArticleTypeMapper() {
    articleTypeFriendlyNames.insert({"Figure", ArticleType::FIGURE});
}

ArticleType ArticleTypeMapper::mapFromString(const string input) {
    return articleTypeFriendlyNames[input];
}


TEST(ArticleTypeMapper, MapsSuccessfully) {
    ArticleTypeMapper mapper;
    ArticleType mappedValue = mapper.mapFromString("Figure");

    ASSERT_THAT(mappedValue, Eq(ArticleType::FIGURE));
}


