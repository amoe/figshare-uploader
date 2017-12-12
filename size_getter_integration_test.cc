#include <gmock/gmock.h>
#include "size_getter.hh"
#include "test_utility.hh"
#include "stubs.hh"
#include "requests.hh"

using ::testing::Eq;

using std::string;

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
    UploadCreationRequest result("", "", sizeGetter->getSize(path));
    return result;
}


TEST(SizeGetterTest, CanGetSize) {
    SizeGetter* getter = new QtSizeGetter;
    int64_t result = getter->getSize("resources/test.xlsx");
    ASSERT_THAT(result, Eq(29907));
}


TEST(SizeGetterTest, CanMakeRequestObject) {
    SizeGetter *getter = new StubFileSizeGetter(43);
    FileSpecGenerator* generator = new FileSpecGeneratorImpl(getter);
    UploadCreationRequest result = generator->getFileSpec("/home/amoe/lazydog.txt");

    // ASSERT_THAT(result.name, "lazydog.txt");
    // ASSERT_THAT(result.md5, Eq("9e107d9d372bb6826bd81d3542a419d6"));
    // ASSERT_THAT(result.size, Eq(43));
}

