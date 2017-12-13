#include "requests.hh"
#include "md5.hh"

class FileSpecGenerator {
public:
    virtual UploadCreationRequest getFileSpec(string path) = 0;
};

class FileSpecGeneratorImpl : public FileSpecGenerator {
public:
    FileSpecGeneratorImpl(SizeGetter* sizeGetter) : sizeGetter(sizeGetter) { }
    UploadCreationRequest getFileSpec(string path);

private:
    SizeGetter* sizeGetter;
};


// This one is the "real" impl that does I/O, hence it's hardcoded to get
// its dependencies directly.
UploadCreationRequest FileSpecGeneratorImpl::getFileSpec(string path) {
    MD5Calculator theCalculator;
    string name;
    string md5;
    const int64_t size = sizeGetter->getSize(path);

    DataSource* fileSource = new FileDataSource(path);
    string md = theCalculator.getMD5(fileSource);
    
    UploadCreationRequest result("", "", size);
    return result;
}
