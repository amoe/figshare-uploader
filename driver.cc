#include <iostream>
#include "driver.hh"
#include "logging.hh"
#include "file_info.hh"
#include "file_part.hh"
#include "excel_row.hh"

void Driver::sayHello() const {
    debugf("hello from driver");
}

void Driver::handleRow(const ExcelRow row) const {
    ArticleCreationRequest acr = articleMapper->mapFromExcel(row.rowData);
    ArticleCreationResponse response = gateway->createArticle(acr);
    string stemArticle = response.location;
    ArticleGetResponse articleData = gateway->getArticle(stemArticle);

    // XXX: Looping logic will one day go here.
    string relationField = row.rowData.at(15);
    UploadCreationRequest ucr = fileSpecGenerator->getFileSpec(relationField);
    handleUpload(stemArticle, ucr);
}

void Driver::handleUpload(const string stemArticle, const UploadCreationRequest ucr) const {
    UploadCreationResponse response = gateway->createUpload(stemArticle, ucr);
    FileInfo fileInfo = gateway->getUploadInfo(response.location);
    UploadContainerInfo uci = gateway->getUploadContainerInfo(
        fileInfo.uploadContainerUrl
    );

    for (FilePart part : uci.parts) {
        handlePart(fileInfo, part);
    }
}

void Driver::handlePart(const FileInfo sourceFile, const FilePart partSpec) const {
    UploadCommand command = partPreparer->prepareUpload(sourceFile, partSpec);
    gateway->putUpload(command);
}
