#include <string>
#include <vector>
#include "ext/optional.hpp"
#include "article_types.hh"
#include "requests.hh"

using nonstd::optional;
using std::vector;
using std::string;

vector<string> ArticleCreationRequest::getAuthors() const {
    return this->authors;
}

string ArticleCreationRequest::getTitle() const {
    return this->title;
}

string ArticleCreationRequest::getDescription() const {
    return this->description;
}

vector<string> ArticleCreationRequest::getKeywords() const {
    return this->keywords;
}

vector<string> ArticleCreationRequest::getReferences() const {
    return this->references;
}

vector<int> ArticleCreationRequest::getCategories() const {
    return this->categories;
}

optional<string> ArticleCreationRequest::getFunding() const {
    return this->funding;
}

ArticleType ArticleCreationRequest::getArticleType() const {
    return this->articleType;
}

int ArticleCreationRequest::getLicense() const {
    return this->license;
}
