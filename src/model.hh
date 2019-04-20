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
    vector<FieldEncoder>& getAvailableEncoders();
    void addFieldEncoder(FieldEncoder f);
    void bindRow(int excelRow, int fieldEncoderIndex);
    void setHeaderFields(vector<string> headerFields);

    // Low-level accessor functions should have const return types if possible.
    const optional<string> getSourceFile() const;
    const vector<string> getHeaderFields() const;

private:
    // The source file may or may not have been picked.
    optional<string> sourceFile;
    vector<FieldEncoder> availableEncoders;
    MappingScheme fieldMappings;
    vector<string> headerFields;
};

#endif /* MODEL_HH */
