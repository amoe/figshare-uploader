#include <string>
#include <vector>
#include <cstddef>
#include "upload_command.hh"

// Vector allocates all memory on the heap.

std::string UploadCommand::getUrl() {
    return this->url;
}

std::vector<std::byte> UploadCommand::getData() {
    return this->data;
}
