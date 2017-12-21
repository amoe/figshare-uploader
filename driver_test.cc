#include <gmock/gmock.h>
#include "figshare_gateway.hh"
#include "responses.hh"
#include "upload_command.hh"
#include "driver.hh"
#include "part_preparer.hh"
#include "object_mother.hh"
#include "upload_container_info.hh"
#include "excel_row.hh"
#include "article_mapper.hh"
#include "progress_reporter.hh"

using namespace testing;

// Now we can store state for multiple tests here.
class DriverTest : public Test {
public:
    DriverTest() {
        driver = new Driver(
            &gateway, &partPreparer, &fileSpecGenerator, &articleMapper
        );
    }

    // These must be public.
    MockPartPreparer partPreparer;
    MockFigshareGateway gateway;
    MockFileSpecGenerator fileSpecGenerator;
    MockArticleMapper articleMapper;
    Driver* driver;
};

TEST_F(DriverTest, canHandleRow) {
    vector<string> rowData = {
        "",    
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",     
        "my_file.tiff",    // Relation field
        "",
        "",
        ""
    };

    ExcelRow row(rowData);

    // Set up expectations, because this row contains one file with exactly two
    // pieces, we expect two PUTs to occur.

    ArticleCreationRequest acr = ObjectMother::makeArticleCreationRequest();
    ArticleCreationResponse aResponse = ObjectMother::makeArticleCreationResponse();
    ArticleGetResponse agr = ObjectMother::makeArticleGetResponse();
    UploadCreationRequest ucr = ObjectMother::makeUploadCreationRequest();
    UploadCreationResponse uResponse = ObjectMother::makeUploadCreationResponse();
    FileInfo fileInfo = ObjectMother::makeFileInfo();
    UploadContainerInfo uploadContainerInfo = ObjectMother::makeUploadContainerInfo(2);
    UploadCommand emptyCommand = ObjectMother::makeUploadCommand();

    EXPECT_CALL(articleMapper, mapFromExcel(_))
        .WillOnce(Return(acr));

    EXPECT_CALL(gateway, createArticle(_))
        .WillOnce(Return(aResponse));

    EXPECT_CALL(gateway, getArticle(_))
        .WillOnce(Return(agr));

    EXPECT_CALL(fileSpecGenerator, getFileSpec(_))
        .WillOnce(Return(ucr));

    EXPECT_CALL(gateway, createUpload(_, _))
        .WillOnce(Return(uResponse));

    EXPECT_CALL(gateway, getUploadInfo(_))
        .WillOnce(Return(fileInfo));

    EXPECT_CALL(gateway, getUploadContainerInfo(_))
      .WillOnce(Return(uploadContainerInfo));

    EXPECT_CALL(partPreparer, prepareUpload(_, _))
        .Times(Exactly(2))
        .WillRepeatedly(Return(emptyCommand));
    EXPECT_CALL(gateway, putUpload(_)).Times(Exactly(2));

    driver->handleRow(row);
}

TEST_F(DriverTest, canHandleUpload) {
    string stemArticle;

    UploadCreationRequest ucr = ObjectMother::makeUploadCreationRequest();
    UploadCreationResponse response = ObjectMother::makeUploadCreationResponse();
    FileInfo fileInfo = ObjectMother::makeFileInfo();
    UploadContainerInfo uploadContainerInfo = ObjectMother::makeUploadContainerInfo(2);
    UploadCommand emptyCommand = ObjectMother::makeUploadCommand();


    EXPECT_CALL(gateway, createUpload(_, _)).WillOnce(Return(response));
    EXPECT_CALL(gateway, getUploadInfo(_)).WillOnce(Return(fileInfo));
    EXPECT_CALL(gateway, getUploadContainerInfo(_))
     .WillOnce(Return(uploadContainerInfo));
    EXPECT_CALL(partPreparer, prepareUpload(_, _))
        .Times(Exactly(2))
        .WillRepeatedly(Return(emptyCommand));

    EXPECT_CALL(gateway, putUpload(_)).Times(Exactly(2));
    driver->handleUpload(stemArticle, ucr);
}

TEST_F(DriverTest, canHandlePart) {
    // We want to check several interactions that are side effecting.
    // For instance, it's pretty obvious that putUpload should be called once
    // by this code.
    // Luckily, FigshareGateway is already an interface.

    string url;
    vector<char> data;
    UploadCommand emptyCommand(url, data);
    

    EXPECT_CALL(partPreparer, prepareUpload(_, _))
      .WillOnce(Return(emptyCommand));

    EXPECT_CALL(gateway, putUpload(_)).Times(AtLeast(1));

    FileInfo sourceFile = ObjectMother::makeFileInfo();
    FilePart partSpec = ObjectMother::makeFilePart(1);

    driver->handlePart(sourceFile, partSpec);
    
    ASSERT_THAT(2 + 2, Eq(4));
}
