#include <iostream>
#include "driver.hh"
#include "logging.hh"
#include "file_info.hh"
#include "file_part.hh"
#include "excel_row.hh"
#include "path_extractor.hh"

void Driver::setProgressReporter(ProgressReporter* reporter) {
    progressReporter = reporter;
}

void Driver::log(string message) const {
    if (progressReporter)
        progressReporter->updateProgress(message);
}

void Driver::handleRow(
    const ExcelRow row, const string inputPath, const MappingScheme& mappingScheme
) const {
    log("Handling row.");

    ArticleCreationRequest acr = articleMapper->mapFromExcel(row.rowData);
    ArticleCreationResponse response = gateway->createArticle(acr);
    string stemArticle = response.location;
    ArticleGetResponse articleData = gateway->getArticle(stemArticle);
    debugf("article created with id %d", articleData.id);


    vector<string> filesToUpload
        = PathExtractor::getRequestedFiles(acr.identifier, inputPath);

    for (const string& thisFile: filesToUpload) {
        debugf("handling upload for file: '%s'", thisFile.c_str());
        UploadCreationRequest ucr = fileSpecGenerator->getFileSpec(thisFile);
        handleUpload(stemArticle, thisFile, ucr);
    }
}

// although the fileinfo does contain the base name of the file.
// it doesn't contain the full path
// so we probably need to pass all things through?????
void Driver::handleUpload(
    const string stemArticle,
    const string sourcePath,
    const UploadCreationRequest ucr
) const {
    UploadCreationResponse response = gateway->createUpload(stemArticle, ucr);
    FileInfo fileInfo = gateway->getUploadInfo(response.location);
    UploadContainerInfo uci = gateway->getUploadContainerInfo(
        fileInfo.uploadContainerUrl
    );

    for (FilePart part : uci.parts) {
        handlePart(sourcePath, fileInfo, part);
    }
}

void Driver::handlePart(
    const string sourcePath, const FileInfo sourceInfo, const FilePart partSpec
) const {
    UploadCommand command = partPreparer->prepareUpload(sourcePath, sourceInfo, partSpec);
    gateway->putUpload(command);
}
