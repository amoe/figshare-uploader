#include <iostream>
#include <gmock/gmock.h>
#include "requests.hh"
#include "responses.hh"

using ::testing::Eq;

// Note that the authorization header needs to be provided in the format
// `Authorization: token <blah>`

class FigshareGateway {
public:
    virtual ArticleCreationResponse createArticle(
        ArticleCreationRequest request
    ) = 0;
};

class HttpFigshareGateway : public FigshareGateway {
public:
    ArticleCreationResponse createArticle(ArticleCreationRequest request);
};

ArticleCreationResponse createArticle(ArticleCreationRequest request) {
    return ArticleCreationResponse(
        "http://nonexistent"
    );
}


TEST(FigshareGatewayTest, ActsAsIExpect) {
    FigshareGateway* gateway = new HttpFigshareGateway;
    
    vector<string> keywords;
    keywords.push_back("Bethlehem");
    keywords.push_back("Crafts");

    vector<string> references;
    references.push_back("https://www.loc.gov/item/mpc2004001373/PP/");

    vector<int> categories;
    categories.push_back(1703);

    vector<string> authors;
    authors.push_back("Freja Howat-Maxted");

    ArticleCreationRequest request(
        "To Serve Man",
        "Some description",
        keywords,
        references,
        categories,
        authors,
        optional<string>("Some grant number"),
        ArticleType::FIGURE,
        1
    );
    

    ArticleCreationResponse response = gateway->createArticle(request);

    std::cout << response.location << std::endl;
}

