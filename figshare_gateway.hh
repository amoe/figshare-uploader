#include "responses.hh"
#include "requests.hh"
#include "http_poster.hh"
#include "http_getter.hh"
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
    HttpFigshareGateway(
        HttpGetter* getter, HttpPoster* poster, CategoryMapper categoryMapper)
        : getter(getter), poster(poster), categoryMapper(categoryMapper) {
    }
    ArticleCreationResponse createArticle(ArticleCreationRequest request);
    UploadCreationResponse createUpload(
        string articleUrl,
        UploadCreationRequest request
    );

private:
    HttpGetter* getter;
    HttpPoster* poster;
    CategoryMapper categoryMapper;
};
