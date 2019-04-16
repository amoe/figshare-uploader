#ifndef MODEL_HH
#define MODEL_HH

#include <string>
#include <vector>
#include "optional.hpp"
#include "mapping_types.hh"

using std::string;
using std::vector;
using nonstd::optional;
using nonstd::nullopt;

class Model {
public:
    Model();
    ~Model();

    void setSourceFile(string newSourceFile);
    optional<string> getSourceFile() const;

    vector<FieldEncoder>& getAvailableEncoders();

private:
    // The source file may or may not have been picked.
    optional<string> sourceFile;

    vector<FieldEncoder> availableEncoders;
};

#endif /* MODEL_HH */
