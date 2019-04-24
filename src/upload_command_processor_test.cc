#include <gmock/gmock.h>
#include "upload_command_processor.hh"
#include "fake_qt_core_application.hh"
#include "logging.hh"

TEST(UploadCommandProcessorTest, ActsAsIExpect) {
    bootQtEventLoop();

    std::vector<char> testData;
    
    testData.push_back(42);
    testData.push_back(64);

    spdlog::info("size: {}", testData.size());

    // This references the first part.
    std::string uploadUrl = "https://fup100010.figshare.com/upload/24803ff1-64c2-4f8f-bb4a-1a4efea23924/1";

    UploadCommand theCommand(uploadUrl, testData);
    UploadCommandProcessor processor;
    
    // processor.process(theCommand);
}



