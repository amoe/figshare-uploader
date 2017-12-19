#include <gmock/gmock.h>
#include <string>
#include <vector>
#include "utility.hh"

using std::vector;
using std::string;
using namespace testing;

class PathExtractor {
public:
    static std::vector<std::string> getRequestedFiles(std::string input) {
        vector<string> splitVersion =  splitSemicolons(input);

        vector<string> result;
        
        for (const string& str : splitVersion) {
            std::cout << str << std::endl;
            if (str.empty() || isWhitespaceOnly(str))
                continue;

            result.push_back(str);
        }
        return result;
    }

private:
    static bool isWhitespaceOnly(std::string input) {
        for (int i = 0; i < input.size(); i++) {
            if (!std::isspace(input.at(i))) 
                return false;
        }

        return true;
    }
};

TEST(MyComponent, EmptyInput) {
    string emptyInput = "";
    vector<string> paths = PathExtractor::getRequestedFiles(emptyInput);
    vector<string> expectedResult = {};

    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(MyComponent, Whitespace) {
    string oneSpace = " ";
    vector<string> paths = PathExtractor::getRequestedFiles(oneSpace);
    
    vector<string> expectedResult = {};

    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(MyComponent, SingleFile) {
    string singleFile = "myfile.tiff";
    vector<string> paths = PathExtractor::getRequestedFiles(singleFile);

    vector<string> expectedResult = {
        "myfile.tiff"
    };
    
    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(MyComponent, MultipleFiles) {
    string multipleFiles = "myfile1.tiff;myfile2.tiff";
    vector<string> paths = PathExtractor::getRequestedFiles(multipleFiles);
    
    vector<string> expectedResult = {
        "myfile1.tiff", "myfile2.tiff"
    };

    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(MyComponent, WhitespaceInMultipleFileSpec) {
    string multipleFilesWithExtraneousWhitespace = "myfile1.tiff ; myfile2.tiff";
    vector<string> paths = PathExtractor::getRequestedFiles(multipleFilesWithExtraneousWhitespace);

    vector<string> expectedResult = {
        "myfile1.tiff", "myfile2.tiff"
    };

    ASSERT_THAT(paths, Eq(expectedResult));
}

