#include <vector>
#include <cstddef>
#include <cstdint>
#include <QFile>
#include <QDebug>
#include <QDataStream>
#include "io_slicer.hh"

std::vector<char> FileSlicer::getDataSlice(
    const int64_t start, const int64_t end
) {
    // We're going to very inefficiently open the file, seek, read the buffer,
    // then close it.  NEVER DO THIS.
    
    QFile theFile(QString::fromStdString(this->filePath));
    bool openResult = theFile.open(QIODevice::ReadOnly);
    if (!openResult)
        qFatal("could not open file");


    bool seekResult = theFile.seek(start);

    qDebug() << "Seek result was" << seekResult;

    int readSize = end - start;

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
