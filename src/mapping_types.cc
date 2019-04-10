#include "mapping_types.hh"

int RowMapping::getSourceRowIndex() const {
    return sourceRowIndex;
}

FieldEncoder RowMapping::getFieldEncoder() const {
    return fieldEncoder;
}

OptionsMap FieldEncoder::getOptions() const {
    return options;
}

Converter FieldEncoder::getConverter() const {
    return converter;
}
