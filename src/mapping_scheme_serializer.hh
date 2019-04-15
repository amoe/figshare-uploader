#ifndef MAPPING_SCHEME_SERIALIZER_HH
#define MAPPING_SCHEME_SERIALIZER_HH

#include <QJsonObject>
#include "mapping_types.hh"

class MappingSchemeSerializer {
public:
    QJsonObject serialize(MappingScheme input) const;
};


#endif /* MAPPING_SCHEME_SERIALIZER_HH */
