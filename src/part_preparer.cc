#include <iostream>
#include <vector>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QByteArray>
#include "part_preparer.hh"
#include "logging.hh"


UploadCommand PartPreparerImpl::prepareUpload(
    const string sourcePath, const FileInfo info, const FilePart part
) {
    std::string url = 
        info.uploadContainerUrl + "/" + std::to_string(part.getPartNumber());

    
    int64_t start = part.getStartOffset();
    int64_t end = part.getEndOffset();

    spdlog::info("will try start: {}", start);
    spdlog::info("will try end: {}", end);

    std::vector<char> data = getDataSlice(
        sourcePath,
        part.getStartOffset(),
        part.getEndOffset()
    );

    return UploadCommand(url, data);
}

vector<char> PartPreparerImpl::getDataSlice(string filePath, int64_t startOffset, int64_t endOffset) {
    // We're going to very inefficiently open the file, seek, read the buffer,
    // then close it.  NEVER DO THIS.
    
    QFile theFile(QString::fromStdString(filePath));
    bool openResult = theFile.open(QIODevice::ReadOnly);
    if (!openResult) {
        spdlog::info("attempt on {} failed", filePath);
        qFatal("could not open file");
    }

    bool seekResult = theFile.seek(startOffset);

    qDebug() << "Seek result was" << seekResult;

    // NB: Avoid off by one error when uploading!
    int readSize = (endOffset - startOffset) + 1;
    std::vector<char> result(readSize);

    // Preallocate a sink buffer
    QByteArray sink(readSize, 0);

    QDataStream in(&theFile);
    int actuallyRead = in.readRawData(sink.data(), readSize);

    if (actuallyRead == -1)
        qFatal("error occurred while reading file");

    if (actuallyRead != readSize) 
        qFatal("somehow read less than full amount");

    // copy from the sink to the result
    for (int i = 0; i < readSize; i++) {
        result[i] = sink.at(i);
    }

    theFile.close();
    
    return result;
}
