#include <iostream>
#include "driver.hh"
#include "logging.hh"
#include "file_info.hh"
#include "file_part.hh"

void Driver::handleUpload(const string stemArticle, const UploadCreationRequest ucr) const {
    UploadCreationResponse response = gateway->createUpload(stemArticle, ucr);
    FileInfo fileInfo = gateway->getUploadInfo(response.location);
    UploadContainerInfo uci = gateway->getUploadContainerInfo(
        fileInfo.uploadContainerUrl
    );

    for (FilePart partSpec : uci.parts) {
        handlePart(fileInfo, partSpec);
    }
}

void Driver::handlePart(const FileInfo sourceFile, const FilePart partSpec) const {
    UploadCommand command = partPreparer->prepareUpload(sourceFile, partSpec);
    gateway->putUpload(command);
}
