#ifndef DEFAULT_FIELD_ENCODERS_HH
#define DEFAULT_FIELD_ENCODERS_HH

namespace default_field_encoders {
    // Initialize standard field encoders

    FieldEncoder DISCARD_ENCODER(
        nullopt,
        ConverterName::DISCARD,
        {},
        {}
    );

    FieldEncoder TITLE_ENCODER(
        optional<TargetField>(TargetField(TargetFieldType::STANDARD, "title")),
        ConverterName::STRING,
        {},
        {}
    );
}

#endif /* DEFAULT_FIELD_ENCODERS_HH */
