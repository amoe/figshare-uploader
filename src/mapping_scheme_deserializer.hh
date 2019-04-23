#ifndef MAPPING_SCHEME_DESERIALIZER_HH
#define MAPPING_SCHEME_DESERIALIZER_HH

#include "mapping_types.hh"

class MappingSchemeDeserializer {
public:
    MappingSchemeDeserializer() { }

    MappingScheme deserialize(string input) const;
};

#endif /* MAPPING_SCHEME_DESERIALIZER_HH */
