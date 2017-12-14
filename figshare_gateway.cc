#include <iostream>
#include "figshare_gateway.hh"
#include "http_poster.hh"
#include "requests.hh"
#include "responses.hh"
#include "article_type_mapper.hh"
#include "article_mapper.hh"
#include "utility.hh"
#include "file_info.hh"
#include "upload_container_info.hh"
#include <QDebug>

using std::vector;
using std::string;

// Note that the authorization header needs to be provided in the format
// `Authorization: token <blah>`

ArticleCreationResponse HttpFigshareGateway::createArticle(
    ArticleCreationRequest request
) {
    ArticleTypeMapper typeMapper;
    ArticleMapper mapper(typeMapper, categoryMapper);

    const string url = "https://api.figshare.com/v2/account/articles";
    const string payload = mapper.mapToFigshare(request);
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
    string location = fetchString(response, "location");
    return UploadCreationResponse(location);
}


FileInfo HttpFigshareGateway::getUploadInfo(string uploadUrl) {
    const string response = getter->request(uploadUrl);

    std::cout << "RAW UPLOAD INFO:" << std::endl;
    std::cout << "---- BEGIN ----" << std::endl;
    std::cout << response << std::endl;
    std::cout << "---- END ----" << std::endl;
    
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

string HttpFigshareGateway::completeUpload(string uploadUrl) {
    const string response = poster->request(uploadUrl, "");
    return response;
}
