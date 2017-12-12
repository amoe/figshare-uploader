#include "responses.hh"
#include "requests.hh"
#include "http_poster.hh"

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
