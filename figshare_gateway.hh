#include "responses.hh"
#include "requests.hh"
#include "http_poster.hh"
#include "category_mapper.hh"

class FigshareGateway {
public:
    virtual ArticleCreationResponse createArticle(
        ArticleCreationRequest request
    ) = 0;

    virtual UploadCreationResponse createUpload(
        string articleUrl,
        UploadCreationRequest request
    ) = 0;

};

class HttpFigshareGateway : public FigshareGateway {
public:
    HttpFigshareGateway(HttpPoster* poster, CategoryMapper categoryMapper)
      : poster(poster), categoryMapper(categoryMapper) {
    }
    ArticleCreationResponse createArticle(ArticleCreationRequest request);
    UploadCreationResponse createUpload(
        string articleUrl,
        UploadCreationRequest request
    );

private:
    HttpPoster* poster;
    CategoryMapper categoryMapper;
};
