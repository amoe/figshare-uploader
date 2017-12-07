#include <gmock/gmock.h>

using ::testing::Eq;
using std::string;
using std::map;

enum class ArticleType {
    FIGURE, MEDIA, DATASET, FILESET, POSTER, PAPER, PRESENTATION, THESIS,
    CODE, METADATA
};

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


