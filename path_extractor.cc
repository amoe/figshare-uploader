#include <cctype>
#include "path_extractor.hh"
#include "utility.hh"

using std::string;
using std::vector;
using std::isspace;


vector<string> PathExtractor::getRequestedFiles(string input) {
    vector<string> splitVersion =  splitSemicolons(input);

    vector<string> result;
        
    for (const string& str : splitVersion) {
        if (str.empty() || isWhitespaceOnly(str))
            continue;

        result.push_back(str);
    }

    return result;
}


bool PathExtractor::isWhitespaceOnly(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isspace(input.at(i))) 
            return false;
    }

    return true;
}
