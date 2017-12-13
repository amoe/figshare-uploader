#include <vector>
#include <cstdint>
#include <QJsonArray>
#include "file_part.hh"

using std::vector;
using std::string;

enum class UploadContainerStatus { PENDING, COMPLETED, ABORTED };

struct UploadContainerInfo {
    UploadContainerInfo(
        string name,
        int64_t size,
        string md5,
        string token,
        UploadContainerStatus status,
        vector<FilePart> parts
    ) : name(name), size(size), md5(md5), token(token), status(status), 
        parts(parts) {}
    
    static UploadContainerInfo fromJson(string jsonText);

    string name;
    int64_t size;
    string md5;
    string token;
    UploadContainerStatus status;
    vector<FilePart> parts;

private:
    static UploadContainerStatus mapStatus(string status);
    static vector<FilePart> mapParts(QJsonArray array);
    static FilePart mapOnePart(QJsonObject object);
};
