#include "figshare_gateway.hh"
#include "http_poster.hh"
#include "requests.hh"
#include "responses.hh"
#include "article_type_mapper.hh"
#include "article_mapper.hh"
#include "utility.hh"

// Note that the authorization header needs to be provided in the format
// `Authorization: token <blah>`


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
