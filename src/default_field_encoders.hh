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

    // when we pass delimiter=null, coerce the entire References field to a
    // single-element JSON array
    const FieldEncoder REFERENCES_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "references")),
        ConverterName::LIST_OF_STRING,
        {},
        {{"delimiter", nullopt}}
    );

    const FieldEncoder CATEGORY_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "categories")),
        ConverterName::LOOKUP_LIST,
        {},
        {{"delimiter", optional<string>(",\\s*")},
         {"resourceName", optional<string>("category")}}
    );

    const FieldEncoder LICENSE_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "license")),
        ConverterName::LOOKUP_VALUE,
        {},
        {{"delimiter", nullopt},
         {"resourceName", optional<string>("license")}}
    );


    const FieldEncoder CONTRIBUTE_FILES_ENCODER(
        nullopt,
        ConverterName::CONTRIBUTE_FILES,
        {},
        {{"delimiter", optional<string>("\\s*;\\s*")}}
    );

    const FieldEncoder DEFINED_TYPE_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "defined_type")),
        ConverterName::LOOKUP_VALUE,
        {},
        {{"resourceName", optional<string>("definedType")}}
    );

    const FieldEncoder AUTHORS_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "authors")),
        ConverterName::LIST_OF_OBJECT,
        {},
        {{"objectField", optional<string>("name")},
         {"delimiter", optional<string>("\\s*,\\s*")}}
    );

    const FieldEncoder GROUP_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "group_id")),
        ConverterName::LOOKUP_VALUE,
        {},
        {{"resourceName", optional<string>("group")}}
    );
}

#endif /* DEFAULT_FIELD_ENCODERS_HH */
