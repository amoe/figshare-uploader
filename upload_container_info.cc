#include <string>
#include "upload_container_info.hh"

UploadContainerInfo UploadContainerInfo::fromJson(string jsonText) {
    string name;
    int64_t size;
    string md5;
    string token;
    UploadContainerStatus status;
    vector<FilePart> parts;

    return UploadContainerInfo(name, size, md5, token, status, parts);
}
