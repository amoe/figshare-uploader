#include "object_mother.hh"

FileInfo ObjectMother::makeFileInfo() {
    string uploadContainerUrl = "http://www.example.com/";
    string fileName = "nonexistent.jpg";
    int64_t id = 12345;
    FileInfo result(uploadContainerUrl, fileName, id);

    return result;
}
