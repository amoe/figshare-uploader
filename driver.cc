#include <iostream>
#include "driver.hh"
#include "logging.hh"
#include "file_info.hh"
#include "file_part.hh"

void Driver::handlePart(const FileInfo sourceFile, const FilePart partSpec) const {
    UploadCommand command = partPreparer->prepareUpload(sourceFile, partSpec);
    gateway->putUpload(command);
}
