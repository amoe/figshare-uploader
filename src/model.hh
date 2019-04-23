#ifndef MODEL_HH
#define MODEL_HH

#include <string>
#include <vector>
#include "optional.hpp"
#include "mapping_types.hh"
#include "interfaces.hh"
#include "default_field_encoders.hh"
#include "converter_registry.hh"

using std::string;
using std::vector;
using nonstd::optional;
using nonstd::nullopt;

class ModelImpl: public Model {
public:
    ModelImpl(const ConverterRegistry& converterRegistry);
    ~ModelImpl();

    void setSourceFile(string newSourceFile);
    vector<FieldEncoder>& getAvailableEncoders();
    void bindRow(int excelRow, int fieldEncoderIndex);
    void setHeaderFields(vector<string> headerFields);

    // Low-level accessor functions should have const return types if possible.
    const optional<string> getSourceFile() const;
    const vector<string> getHeaderFields() const;

    // This observing reference is used by the field mapping model.
    const MappingScheme& getFieldMappings() const;

    void replaceFieldMappings(MappingScheme newMappingScheme);

    const ConverterRegistry& getConverterRegistry() const;


    void addFieldEncoder(FieldEncoder f);
    void replaceFieldEncoder(int index, FieldEncoder f);

    void dumpMappingScheme() const;

private:
    void initializeMappingScheme();

    // The source file may or may not have been picked.
    optional<string> sourceFile;
    vector<FieldEncoder> availableEncoders;
    MappingScheme fieldMappings;
    vector<string> headerFields;
    const ConverterRegistry& converterRegistry;
};

#endif /* MODEL_HH */
