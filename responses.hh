#ifndef RESPONSES_HH
#define RESPONSES_HH

#include <string>

using std::string;

struct ArticleCreationResponse {
    ArticleCreationResponse(string location)
        : location(location) { }
    string location;
};

struct UploadCreationResponse {
    UploadCreationResponse(string location)
        : location(location) { }
    string location;
};

#endif // RESPONSES_HH
