#ifndef MODEL_HH
#define MODEL_HH

#include <string>
#include "optional.hpp"

using std::string;
using nonstd::optional;
using nonstd::nullopt;

class Model {
public:
    Model(): sourceFile(nullopt) { }

    void setSourceFile(string newSourceFile);
    optional<string> getSourceFile() const;

private:
    // The source file may or may not have been picked.
    optional<string> sourceFile;
};

#endif /* MODEL_HH */
