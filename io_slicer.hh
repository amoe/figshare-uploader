#ifndef IO_SLICER_HH
#define IO_SLICER_HH

#include <cstddef>
#include <vector>
#include <string>
#include <cstdint>

class IOSlicer {
public:
    // Pure virtual.
    virtual std::vector<char> getDataSlice(
        const int64_t start, const int64_t end
    ) = 0;
};

class FileSlicer : public IOSlicer {
public:
    FileSlicer(std::string filePath) : filePath(filePath) { }
    std::vector<char> getDataSlice(const int64_t start, const int64_t end);

private:
    std::string filePath;
};

#endif // IO_SLICER_HH
