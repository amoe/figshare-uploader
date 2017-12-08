#include <string>
#include <vector>
#include "ext/optional.hpp"
#include "article_types.hh"

using nonstd::optional;
using std::vector;
using std::string;

class ArticleCreationRequest {
public:
    ArticleCreationRequest(
        string title, string description,
        vector<string> keywords,
        vector<string> references,
        vector<int> categories,
        vector<string> authors,
        optional<string> funding,
        ArticleType articleType,
        int license
    ) : title(title), description(description), keywords(keywords),
        references(references), categories(categories),  authors(authors),
        funding(funding), articleType(articleType), license(license)
        { }
    string getTitle() const;
    string getDescription() const;
    vector<string> getKeywords() const;
    vector<string> getReferences() const;
    vector<int> getCategories() const;
    vector<string> getAuthors() const;
    optional<string> getFunding() const;
    ArticleType getArticleType() const;
    int getLicense() const;
    
private:
    string title;
    string description;
    vector<string> keywords;
    vector<string> references;
    vector<int> categories;
    vector<string> authors;
    optional<string> funding;
    ArticleType articleType;
    int license;
};
