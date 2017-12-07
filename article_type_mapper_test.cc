#include <gmock/gmock.h>
#include "article_types.hh"
#include "article_type_mapper.hh"

using ::testing::Eq;

TEST(ArticleTypeMapper, MapsSuccessfullyFromExcelSyntax) {
    ArticleTypeMapper mapper;
    ArticleType mappedValue = mapper.mapFromString("Figure");

    ASSERT_THAT(mappedValue, Eq(ArticleType::FIGURE));
}



TEST(ArticleTypeMapper, MapsSuccessfullyToFigshareSyntax) {
    ArticleTypeMapper mapper;
    string mappedValue = mapper.toFigshare(ArticleType::FIGURE);

    ASSERT_THAT(mappedValue, Eq("figure"));
}


