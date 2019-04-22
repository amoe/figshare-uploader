#ifndef ENUM_CLASS_HASH_HH
#define ENUM_CLASS_HASH_HH

// This is basically a hack to allow storing enum classes in an unordered_map,
// and it should definitely be moved somewhere more useful.

#include <cstddef>

using std::size_t;

struct EnumClassHash {
    template <typename T>
    size_t operator()(T t) const {
        return static_cast<size_t>(t);
    }
};


#endif /* ENUM_CLASS_HASH_HH */
