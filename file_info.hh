#ifndef FILE_INFO_HH
#define FILE_INFO_HH

#include <string>

using std::string;

struct FileInfo {
    FileInfo(std::string uploadContainerUrl, std::string fileName, int64_t id)
      : uploadContainerUrl(uploadContainerUrl), fileName(fileName) { }
    
    // This is a separate API that's under a "fupN.figshare.com" domain.
    std::string uploadContainerUrl;
    std::string fileName;
    int64_t id;   // This represents the ARTICLE ID for some reason that I can't fathom.

    static FileInfo fromJson(string jsonText);
};

#endif // FILE_INFO_HH
