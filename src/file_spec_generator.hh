#ifndef FILE_SPEC_GENERATOR_HH
#define FILE_SPEC_GENERATOR_HH

#include <gmock/gmock.h>
#include "requests.hh"
#include "md5.hh"
#include "utility.hh"
#include "size_getter.hh"

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

class MockFileSpecGenerator : public FileSpecGenerator {
public:
    MOCK_METHOD1(getFileSpec, UploadCreationRequest(string path));
};

#endif // FILE_SPEC_GENERATOR_HH
