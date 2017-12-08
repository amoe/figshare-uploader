#include <iostream>
#include <gmock/gmock.h>
#include "requests.hh"
#include "raw_literals.hh"
#include "responses.hh"
#include "http_poster.hh"
#include "stubs.hh"
#include "utility.hh"
#include "article_mapper.hh"
#include "article_type_mapper.hh"

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
    HttpFigshareGateway(HttpPoster* poster) : poster(poster) {
    }
    ArticleCreationResponse createArticle(ArticleCreationRequest request);

private:
    HttpPoster* poster;
};

ArticleCreationResponse HttpFigshareGateway::createArticle(
    ArticleCreationRequest request
) {
    ArticleTypeMapper typeMapper;
    ArticleMapper mapper(typeMapper);

    const string url = "https://api.figshare.com/v2/account/articles";
    const string payload = mapper.mapToFigshare(request);
    const string response = poster->request(url, payload);
    string location = fetchString(response, "location");
    return ArticleCreationResponse(location);
}


TEST(FigshareGatewayTest, ActsAsIExpect) {
    HttpPoster* poster = new StubHttpPoster(
        raw_literals::fakeArticleCreationResponse
    );
    FigshareGateway* gateway = new HttpFigshareGateway(poster);
    
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

    ASSERT_THAT(response.location, Eq("http://nonexistent.net/"));
}

