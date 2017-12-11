#include <string>
#include <vector>
#include <cstddef>

class UploadCommand {
public:
    UploadCommand(std::string url, std::vector<std::byte> data) 
        : url(url), data(data) {}
    std::string getUrl();
    std::vector<std::byte> getData();
private:
    std::string url;
    std::vector<std::byte> data;
};
