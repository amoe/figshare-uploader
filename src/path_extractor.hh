#include <string>
#include <vector>

using std::vector;
using std::string;

class PathExtractor {
public:
    static std::vector<std::string> getRequestedFiles(
        std::string uploadSpec, std::string xlsxPath
    );

private:
    static bool isWhitespaceOnly(std::string input);
};
