# Field encoder definitions

To declare a very normal field:

    TargetField targetField(TargetFieldType::STANDARD, "name");
    FieldEncoder titleEncoder(targetField, Converter::STRING, {}, {});

For more detailed examples, you can look at the list of default field encoders.
They are declared in `default_field_encoders.hh`.


## Validating XSLX documents

You can check out this tool: https://github.com/vindvaki/xlsx-validator

It should run under Mono.

Or this example.  https://blogs.msdn.microsoft.com/ericwhite/2010/03/04/validate-open-xml-documents-using-the-open-xml-sdk-2-0/
