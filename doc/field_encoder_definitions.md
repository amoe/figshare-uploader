# Field encoder definitions

To declare a very normal field:

    TargetField targetField(TargetFieldType::STANDARD, "name");
    FieldEncoder titleEncoder(targetField, Converter::STRING, {}, {});

