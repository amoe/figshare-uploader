#ifndef SIZE_GETTER_HH
#define SIZE_GETTER_HH

#include <string>
#include <cstdint>

using std::string;

class SizeGetter {
public:
    virtual int64_t getSize(string path) = 0;
};

class QtSizeGetter : public SizeGetter {
public:
    int64_t getSize(string path);

};

#endif // SIZE_GETTER_HH
