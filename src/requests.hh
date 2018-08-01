#ifndef REQUESTS_HH
#define REQUESTS_HH

#include <string>
#include <vector>
#include <map>
#include "optional.hpp"
#include "article_types.hh"

using nonstd::optional;
using std::vector;
using std::string;
using std::map;

// These should probably all not be copied, but hey.
struct ArticleCreationRequest {
    ArticleCreationRequest(
        string title, string description,
        vector<string> keywords,
        vector<string> references,
        vector<int> categories,
        vector<string> authors,
        optional<string> funding,
        ArticleType articleType,
        int license,
        string identifier,
        string groupName,
        map<string, string> customFields
    ) : title(title), description(description), keywords(keywords),
        references(references), categories(categories),  authors(authors),
        funding(funding), articleType(articleType), license(license),
        identifier(identifier), groupName(groupName), customFields(customFields)
        { }

    string title;
    string description;
    vector<string> keywords;
    vector<string> references;
    vector<int> categories;
    vector<string> authors;
    optional<string> funding;
    ArticleType articleType;
    int license;
    string identifier;
    string groupName;
    map<string, string> customFields;
};

struct UploadCreationRequest {
    UploadCreationRequest(string name, string md5, int64_t size)
        : name(name), md5(md5), size(size) { }

    string toJson() const;

    string name;   // the *relative* name of the file -- can't be used to open
    string md5;    // This is the hex representation not the binary one
    int64_t size;
};


#endif // REQUESTS_HH
