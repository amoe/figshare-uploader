#include <iostream>
#include "logging.hh"
#include "figshare_gateway.hh"
#include "custom_field_mapper.hh"
#include "http_poster.hh"
#include "requests.hh"
#include "responses.hh"
#include "article_type_mapper.hh"
#include "utility.hh"
#include "file_info.hh"
#include "upload_container_info.hh"
#include "group_mapper.hh"
#include <QDebug>
#include <QJsonDocument>

using std::vector;
using std::string;

// Note that the authorization header needs to be provided in the format
// `Authorization: token <blah>`
ArticleCreationResponse HttpFigshareGateway::createArticle(QJsonObject articleObject) {
    const string url = "https://api.figshare.com/v2/account/articles";
    const string payload = QString::fromUtf8(
        QJsonDocument(articleObject).toJson()
    ).toStdString();
    const string response = poster->request(url, payload);
    string location = fetchString(response, "location");
    return ArticleCreationResponse(location);
}


ArticleGetResponse HttpFigshareGateway::getArticle(string url) {
    const string response = getter->request(url);
    return ArticleGetResponse::fromJson(response);
}


UploadCreationResponse HttpFigshareGateway::createUpload(
    string articleUrl,
    UploadCreationRequest request
) {
    const string url = articleUrl + "/files";
    const string payload = request.toJson();
    const string response = poster->request(url, payload);
    spdlog::info("create upload response was {}", response);
    string location = fetchString(response, "location");
    spdlog::info("fetched string {}", location);
    return UploadCreationResponse(location);
}


FileInfo HttpFigshareGateway::getUploadInfo(string uploadUrl) {
    const string response = getter->request(uploadUrl);

    spdlog::info("RAW UPLOAD INFO");
    spdlog::info("---- BEGIN ----");
    spdlog::info("{}", response.c_str());
    spdlog::info("---- END   ----");
    
    return FileInfo::fromJson(response);;
}

UploadContainerInfo HttpFigshareGateway::getUploadContainerInfo(
    string uploadContainerUrl
) {
    const string response = getter->request(uploadContainerUrl);
    return UploadContainerInfo::fromJson(response);
}


PartPutResponse HttpFigshareGateway::putUpload(UploadCommand uc) {
    vector<char> buffer = uc.getData();
    string payload(buffer.begin(), buffer.end());

    
    const string response = putter->request(uc.getUrl(), payload);
    PartPutResponse result;

    return result;
}

// The completion URL should be provided to us as the location attribute of an
// UploadCreationResponse.
string HttpFigshareGateway::completeUpload(string completeUrl) {
    // I assume that a payload of an empty string is equivalent to data=None in
    // python-requests.
    const string response = poster->request(completeUrl, "");
    return response;
}

