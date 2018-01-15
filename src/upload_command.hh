#ifndef UPLOAD_COMMAND_HH
#define UPLOAD_COMMAND_HH

#include <string>
#include <vector>
#include <cstddef>

class UploadCommand {
public:
    UploadCommand(std::string url, std::vector<char> data) 
        : url(url), data(data) {}
    std::string getUrl();
    std::vector<char> getData();
private:
    std::string url;
    std::vector<char> data;
};

#endif // UPLOAD_COMMAND_HH
