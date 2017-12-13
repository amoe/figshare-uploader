#include "responses.hh"
#include "requests.hh"
#include "http_poster.hh"
#include "http_getter.hh"
#include "category_mapper.hh"
#include "file_info.hh"

class FigshareGateway {
public:
    virtual ArticleCreationResponse createArticle(
        ArticleCreationRequest request
    ) = 0;

    virtual UploadCreationResponse createUpload(
        string articleUrl,
        UploadCreationRequest request
    ) = 0;

    virtual FileInfo getUploadInfo(
        string uploadUrl
    ) = 0;


};

class HttpFigshareGateway : public FigshareGateway {
public:
    HttpFigshareGateway(
        HttpGetter* getter, HttpPoster* poster, CategoryMapper categoryMapper)
        : getter(getter), poster(poster), categoryMapper(categoryMapper) {
    }

    // These methods form the official Figshare API
    ArticleCreationResponse createArticle(ArticleCreationRequest request);
    UploadCreationResponse createUpload(
        string articleUrl,
        UploadCreationRequest request
    );
    FileInfo getUploadInfo(string uploadUrl);

    // These methods are part of the "upload service", which is a separate API.
    // This doesn't need authentication.
//    UploadContainerInfo getUploadContainerInfo(string uploadContainerUrl);

private:
    HttpGetter* getter;
    HttpPoster* poster;
    CategoryMapper categoryMapper;
};
