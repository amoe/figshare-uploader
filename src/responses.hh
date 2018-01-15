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

struct PartPutResponse {
    PartPutResponse() { }
};

struct ArticleGetResponse {
    ArticleGetResponse(int id) : id(id) {}

    int id;
    static ArticleGetResponse fromJson(string jsonText);
};

#endif // RESPONSES_HH
