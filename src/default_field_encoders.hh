#ifndef DEFAULT_FIELD_ENCODERS_HH
#define DEFAULT_FIELD_ENCODERS_HH

#include "optional.hpp"

using nonstd::optional;
using nonstd::nullopt;

namespace default_field_encoders {
    // Initialize standard field encoders
    const FieldEncoder DISCARD_ENCODER(
        nullopt,
        ConverterName::DISCARD,
        {},
        {}
    );

    const FieldEncoder TITLE_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "title")),
        ConverterName::STRING,
        {},
        {}
    );

    const FieldEncoder DESCRIPTION_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "description")),
        ConverterName::STRING,
        {},
        {}
    );

    const FieldEncoder KEYWORDS_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "keywords")),
        ConverterName::LIST_OF_STRING,
        {},
        {{"delimiter", optional<string>(",\\s*")}}
    );
}

#endif /* DEFAULT_FIELD_ENCODERS_HH */
