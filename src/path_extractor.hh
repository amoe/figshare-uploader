#include <string>
#include <vector>

using std::vector;
using std::string;

class PathExtractor {
public:
    static vector<string> getRequestedFiles(string uploadSpec, string xlsxPath);
    static vector<string> resolvePaths(vector<string> speccedPaths, string sourceExcelPath);
};
