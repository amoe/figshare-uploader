#include "file_spec_generator.hh"

// This one is the "real" impl that does I/O, hence it's hardcoded to get
// its dependencies directly.
UploadCreationRequest FileSpecGeneratorImpl::getFileSpec(string path) {
    MD5Calculator theCalculator;
    string md5;
    const int64_t size = sizeGetter->getSize(path);

    DataSource* fileSource = new FileDataSource(path);
    string md = theCalculator.getMD5(fileSource);
    
    UploadCreationRequest result(basename(path), md, size);
    return result;
}
