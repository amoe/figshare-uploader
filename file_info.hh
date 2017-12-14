#ifndef FILE_INFO_HH
#define FILE_INFO_HH

struct FileInfo {
    FileInfo(std::string uploadContainerUrl, std::string fileName, int64_t id)
      : uploadContainerUrl(uploadContainerUrl), fileName(fileName) { }
    
    // This is a separate API that's under a "fupN.figshare.com" domain.
    std::string uploadContainerUrl;
    std::string fileName;
    int64_t id;
};

#endif // FILE_INFO_HH
