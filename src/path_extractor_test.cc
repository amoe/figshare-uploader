#include <gmock/gmock.h>
#include <string>
#include <vector>
#include "path_extractor.hh"

using namespace testing;
using std::string;
using std::vector;

TEST(PathExtractorTest, EmptyInput) {
    string emptyInput = "";
    vector<string> paths = PathExtractor::getRequestedFiles(emptyInput, "/home/fry/upload.xlsx");
    vector<string> expectedResult = {};

    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(PathExtractorTest, Whitespace) {
    string oneSpace = " ";
    vector<string> paths = PathExtractor::getRequestedFiles(oneSpace, "/home/fry/upload.xlsx");
    
    vector<string> expectedResult = {};

    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(PathExtractorTest, SingleFile) {
    string singleFile = "myfile.tiff";
    vector<string> paths = PathExtractor::getRequestedFiles(singleFile, "/home/fry/upload.xlsx");

    vector<string> expectedResult = {
        "/home/fry/myfile.tiff"
    };
    
    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(PathExtractorTest, MultipleFiles) {
    string multipleFiles = "myfile1.tiff;myfile2.tiff";
    vector<string> paths = PathExtractor::getRequestedFiles(multipleFiles, "/home/fry/upload.xlsx");
    
    vector<string> expectedResult = {
        "/home/fry/myfile1.tiff",
        "/home/fry/myfile2.tiff"
    };

    ASSERT_THAT(paths, Eq(expectedResult));
}

TEST(PathExtractorTest, WhitespaceInMultipleFileSpec) {
    string multipleFilesWithExtraneousWhitespace = "myfile1.tiff ; myfile2.tiff";
    vector<string> paths = PathExtractor::getRequestedFiles(
        multipleFilesWithExtraneousWhitespace, "/home/fry/upload.xlsx"
    );

    vector<string> expectedResult = {
        "/home/fry/myfile1.tiff",
        "/home/fry/myfile2.tiff"
    };

    ASSERT_THAT(paths, Eq(expectedResult));
}

