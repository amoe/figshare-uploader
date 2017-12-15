#ifndef FIGSHARE_GATEWAY_HH
#define FIGSHARE_GATEWAY_HH

#include <gmock/gmock.h>
#include "responses.hh"
#include "requests.hh"
#include "http_poster.hh"
#include "http_getter.hh"
#include "category_mapper.hh"
#include "file_info.hh"
#include "upload_container_info.hh"
#include "upload_command.hh"
#include "http_putter.hh"

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

    virtual UploadContainerInfo getUploadContainerInfo(
        string uploadContainerUrl
    ) = 0;

    virtual PartPutResponse putUpload(UploadCommand uc) = 0;
    virtual string completeUpload(int articleId, int uploadId) = 0;

    virtual ArticleGetResponse getArticle(string url) = 0;

};

class HttpFigshareGateway : public FigshareGateway {
public:
    HttpFigshareGateway(
        HttpGetter* getter, HttpPoster* poster, HttpPutter* putter,
        CategoryMapper categoryMapper)
        : getter(getter), poster(poster), putter(putter),
          categoryMapper(categoryMapper) {
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
    UploadContainerInfo getUploadContainerInfo(string uploadContainerUrl);
    PartPutResponse putUpload(UploadCommand uc);

    string completeUpload(int articleId, int uploadId);

    ArticleGetResponse getArticle(string url);


private:
    HttpGetter* getter;
    HttpPoster* poster;
    HttpPutter* putter;
    CategoryMapper categoryMapper;
};

class MockFigshareGateway : public FigshareGateway {
public:
    MOCK_METHOD1(createArticle, ArticleCreationResponse(ArticleCreationRequest request));
    MOCK_METHOD2(
        createUpload, 
        UploadCreationResponse(string articleUrl, UploadCreationRequest request)
    );
    MOCK_METHOD1(getUploadInfo, FileInfo(string uploadUrl));
    MOCK_METHOD1(
        getUploadContainerInfo,
        UploadContainerInfo(string uploadContainerUrl)
    );
    MOCK_METHOD1(putUpload, PartPutResponse(UploadCommand uc));
    MOCK_METHOD2(completeUpload, string(int articleId, int uploadId));
    MOCK_METHOD1(getArticle, ArticleGetResponse(string url));
};

#endif // FIGSHARE_GATEWAY_HH
