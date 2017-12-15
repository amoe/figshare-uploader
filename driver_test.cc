#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "responses.hh"
#include "upload_command.hh"
#include "driver.hh"
#include "part_preparer.hh"
#include "object_mother.hh"
#include "upload_container_info.hh"

using namespace testing;

// Now we can store state for multiple tests here.
class DriverTest : public Test {
};

TEST_F(DriverTest, canHandleUpload) {
    string stemArticle;

    string md5;
    string name;
    int64_t size;
    UploadCreationRequest ucr(name, md5, size);

    MockPartPreparer partPreparer;
    MockFigshareGateway gateway;
    Driver driver(&gateway, &partPreparer);

    UploadCreationResponse response("http://www.some-location.com/");
    FileInfo fileInfo = ObjectMother::makeFileInfo();
    UploadContainerInfo uploadContainerInfo = ObjectMother::makeUploadContainerInfo(2);

    string url;
    vector<char> data;
    UploadCommand emptyCommand(url, data);


    EXPECT_CALL(gateway, createUpload(_, _)).WillOnce(Return(response));
    EXPECT_CALL(gateway, getUploadInfo(_)).WillOnce(Return(fileInfo));
    EXPECT_CALL(gateway, getUploadContainerInfo(_))
     .WillOnce(Return(uploadContainerInfo));
    EXPECT_CALL(partPreparer, prepareUpload(_, _))
        .Times(Exactly(2))
        .WillRepeatedly(Return(emptyCommand));

    EXPECT_CALL(gateway, putUpload(_)).Times(Exactly(2));
    driver.handleUpload(stemArticle, ucr);
}

TEST_F(DriverTest, canHandlePart) {
    // We want to check several interactions that are side effecting.
    // For instance, it's pretty obvious that putUpload should be called once
    // by this code.
    // Luckily, FigshareGateway is already an interface.

    MockPartPreparer partPreparer;
    MockFigshareGateway gateway;
    Driver driver(&gateway, &partPreparer);

    string url;
    vector<char> data;
    UploadCommand emptyCommand(url, data);
    

    EXPECT_CALL(partPreparer, prepareUpload(_, _))
      .WillOnce(Return(emptyCommand));

    EXPECT_CALL(gateway, putUpload(_)).Times(AtLeast(1));

    FileInfo sourceFile = ObjectMother::makeFileInfo();
    FilePart partSpec = ObjectMother::makeFilePart(1);

    driver.handlePart(sourceFile, partSpec);
    
    ASSERT_THAT(2 + 2, Eq(4));
}
