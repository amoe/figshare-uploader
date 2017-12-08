#include <string>

struct ArticleCreationResponse {
    ArticleCreationResponse(string location)
        : location(location) { }
    string location;
};
