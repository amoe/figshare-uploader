#include <cstdint>
#include <QString>
#include <QFileInfo>
#include "size_getter.hh"


int64_t QtSizeGetter::getSize(string path) {
    QString qPath = QString::fromStdString(path);

    QFileInfo fileInfo(qPath);

    auto result = (int64_t) fileInfo.size();

    // this can mean the file doesn't exist, there was an error, or that
    // it has zero length, bad qt api design, but we don't care about the user
    // trying to upload zero length files
    if (!result)
        throw std::runtime_error("refusing to get size of zero-length file");

    return result;
}
