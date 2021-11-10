#ifndef FIGSHARE_GATEWAY_HH
#define FIGSHARE_GATEWAY_HH

#include "responses.hh"
#include "requests.hh"
#include "http_poster.hh"
#include "http_getter.hh"
#include "category_mapper.hh"
#include "file_info.hh"
#include "upload_container_info.hh"
#include "upload_command.hh"
#include "http_putter.hh"
#include "group_mapper.hh"

class FigshareGateway {
public:
    virtual ArticleCreationResponse createArticle(
        QJsonObject articleObject
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
    virtual string completeUpload(string completeUrl) = 0;

    virtual ArticleGetResponse getArticle(string url) = 0;

};

class HttpFigshareGateway : public FigshareGateway {
public:
    HttpFigshareGateway(
        HttpGetter* getter, HttpPoster* poster, HttpPutter* putter,
        CategoryMapper categoryMapper, GroupMapper* groupMapper)
        : getter(getter), poster(poster), putter(putter),
          categoryMapper(categoryMapper), groupMapper(groupMapper) { }

    // These methods form the official Figshare API
    ArticleCreationResponse createArticle(ArticleCreationRequest request);
    ArticleCreationResponse createArticle(QJsonObject articleObject);

    UploadCreationResponse createUpload(
        string articleUrl,
        UploadCreationRequest request
    );
    FileInfo getUploadInfo(string uploadUrl);

    // These methods are part of the "upload service", which is a separate API.
    // This doesn't need authentication.
    UploadContainerInfo getUploadContainerInfo(string uploadContainerUrl);
    PartPutResponse putUpload(UploadCommand uc);

    string completeUpload(string completeUrl);

    ArticleGetResponse getArticle(string url);


private:
    HttpGetter* getter;
    HttpPoster* poster;
    HttpPutter* putter;
    CategoryMapper categoryMapper;
    GroupMapper* groupMapper;
};

#endif // FIGSHARE_GATEWAY_HH
