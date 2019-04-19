#ifndef MODEL_HH
#define MODEL_HH

#include <string>
#include <vector>
#include "optional.hpp"
#include "mapping_types.hh"
#include "interfaces.hh"

using std::string;
using std::vector;
using nonstd::optional;
using nonstd::nullopt;

class ModelImpl: public Model {
public:
    ModelImpl();
    ~ModelImpl();

    void setSourceFile(string newSourceFile);
    optional<string> getSourceFile() const;
    vector<FieldEncoder>& getAvailableEncoders();
    void addFieldEncoder(FieldEncoder f);

private:
    // The source file may or may not have been picked.
    optional<string> sourceFile;
    vector<FieldEncoder> availableEncoders;
    MappingScheme fieldMappings;
};

#endif /* MODEL_HH */
