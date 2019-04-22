#include <cctype>
#include "path_extractor.hh"
#include "utility.hh"

using std::string;
using std::vector;
using std::isspace;

// The path extractor also has a responsibility to resolve the paths into 
// absolute ones.

vector<string> PathExtractor::getRequestedFiles(
    string uploadSpec, string xlsxPath
) {
    vector<string> splitVersion =  splitByRegexp(uploadSpec, "\\s*[;,]\\s*");
    return resolvePaths(splitVersion, xlsxPath);
}

vector<string> PathExtractor::resolvePaths(
    vector<string> speccedPaths, string sourceExcelPath
) {
    vector<string> result;
    for (const string& str : speccedPaths) {
        if (str.empty() || isWhitespaceOnly(str))
            continue;
        result.push_back(resolvePath(sourceExcelPath, str));
    }
    return result;
}
