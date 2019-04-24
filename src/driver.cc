#include <iostream>
#include "driver.hh"
#include "logging.hh"
#include "file_info.hh"
#include "file_part.hh"
#include "excel_row.hh"
#include "path_extractor.hh"

void DriverImpl::setProgressReporter(ProgressReporter* reporter) {
    progressReporter = reporter;
}

void DriverImpl::log(string message) const {
    if (progressReporter)
        progressReporter->updateProgress(message);
}

void DriverImpl::handleRow(
    const ExcelRow row, const string inputPath, const MappingScheme& mappingScheme
) const {
    log("Handling row");

    MappingOutput result = mappingEngine->convert(row.rowData, mappingScheme);
    QJsonObject articleObject = result.getArticleObject();
    vector<string> sourcePaths = result.getSourcePaths();
    ArticleCreationResponse response = gateway->createArticle(articleObject);
    string stemArticle = response.location;
    ArticleGetResponse articleData = gateway->getArticle(stemArticle);
    debugf("article created with id %d", articleData.id);

    vector<string> filesToUpload
        = PathExtractor::resolvePaths(sourcePaths, inputPath);

    for (const string& thisFile: filesToUpload) {
        debugf("handling upload for file: '%s'", thisFile.c_str());
        UploadCreationRequest ucr = fileSpecGenerator->getFileSpec(thisFile);
        handleUpload(stemArticle, thisFile, ucr);
    }
}

// although the fileinfo does contain the base name of the file.
// it doesn't contain the full path
// so we probably need to pass all things through?????
void DriverImpl::handleUpload(
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

void DriverImpl::handlePart(
    const string sourcePath, const FileInfo sourceInfo, const FilePart partSpec
) const {
    UploadCommand command = partPreparer->prepareUpload(sourcePath, sourceInfo, partSpec);
    gateway->putUpload(command);
}
