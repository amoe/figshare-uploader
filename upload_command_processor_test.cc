#include <gmock/gmock.h>
#include "upload_command_processor.hh"
#include "fake_qt_core_application.hh"

TEST(UploadCommandProcessorTest, ActsAsIExpect) {
    bootQtEventLoop();

    std::cout << "hello world" << std::endl;

    std::vector<char> testData;
    
    testData.push_back(42);
    testData.push_back(64);

    std::cout << "size: " << testData.size() << std::endl;

    // This references the first part.
    std::string uploadUrl = "https://fup100010.figshare.com/upload/24803ff1-64c2-4f8f-bb4a-1a4efea23924/1";

    UploadCommand theCommand(uploadUrl, testData);
    UploadCommandProcessor processor;
    
    std::cout << "XXX: skipping send, see test" << std::endl;
    // processor.process(theCommand);
}



