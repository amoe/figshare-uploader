#include <gmock/gmock.h>
#include "raw_literals.hh"
#include "category_mapper.hh"

using std::string;
using std::map;
using ::testing::Eq;


TEST(CategoryMapper, MapsCategorySuccessfully) {
    CategoryMapper mapper(raw_literals::categoryResponse);
    int categoryId = mapper.mapTitle("Middle Eastern and African History");

    ASSERT_THAT(categoryId, Eq(1703));
}


