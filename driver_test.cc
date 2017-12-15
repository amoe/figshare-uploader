#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "responses.hh"
#include "upload_command.hh"
#include "driver.hh"
#include "part_preparer.hh"

using namespace testing;

// Now we can store state for multiple tests here.
class DriverTest : public Test {
};

TEST_F(DriverTest, canHandlePart) {
    // We want to check several interactions that are side effecting.
    // For instance, it's pretty obvious that putUpload should be called once
    // by this code.
    // Luckily, FigshareGateway is already an interface.

    MockPartPreparer partPreparer;
    MockFigshareGateway gateway;
    Driver driver(&gateway, &partPreparer);

    EXPECT_CALL(gateway, putUpload(_)).Times(AtLeast(1));

    string uploadContainerUrl = "http://www.example.com/";
    string fileName = "nonexistent.jpg";
    int64_t id = 12345;

    int partNumber = 1;
    int64_t startOffset = 10;
    int64_t endOffset = 20;
    bool isLocked = false;
    FilePartStatus status = FilePartStatus::PENDING;

    FileInfo sourceFile(uploadContainerUrl, fileName, id);
    FilePart partSpec(partNumber, startOffset, endOffset, isLocked, status);

    driver.handlePart(sourceFile, partSpec);
    
    ASSERT_THAT(2 + 2, Eq(4));
}
