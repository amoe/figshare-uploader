#include <gmock/gmock.h>
#include "upload_command.hh"
#include "upload_command_processor.hh"

using ::testing::Eq;

TEST(UploadCommandProcessor, ActsAsIExpect) {
    // start event loop
    QCoreApplication app(argc, argv);

    std::cout << "hello world" << std::endl;

    std::vector<std::byte> testData;
    
    testData.push_back(std::byte{42});
    testData.push_back(std::byte{64});

    std::cout << "size: " << testData.size() << std::endl;

    // This references the first part.
    std::string uploadUrl = "https://fup100010.figshare.com/upload/24803ff1-64c2-4f8f-bb4a-1a4efea23924/1";

    UploadCommand theCommand(uploadUrl, testData);
    UploadCommandProcessor processor;
    
    processor.process(theCommand);
}
