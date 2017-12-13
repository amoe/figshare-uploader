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


UploadCreationRequest FileSpecGeneratorImpl::getFileSpec(string path) {
    string name;
    string md5;
    const int64_t size = sizeGetter->getSize(path);
    
    UploadCreationRequest result("", "", size);
    return result;
}
