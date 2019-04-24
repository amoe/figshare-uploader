# Field encoder definitions

To declare a very normal field:

    TargetField targetField(TargetFieldType::STANDARD, "name");
    FieldEncoder titleEncoder(targetField, Converter::STRING, {}, {});

For more detailed examples, you can look at the list of default field encoders.
They are declared in `default_field_encoders.hh`.

