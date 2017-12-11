#ifndef FILE_INFO_HH
#define FILE_INFO_HH

class FileInfo {
public:
    FileInfo(std::string uploadUrl, std::string fileName)
      : uploadUrl(uploadUrl), fileName(fileName) { }
    std::string getFileName() const;
    std::string getUploadUrl() const;

private:
    std::string uploadUrl;
    std::string fileName;
};

#endif // FILE_INFO_HH
