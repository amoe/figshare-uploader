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

ConverterName FieldEncoder::getConverterName() const {
    return converterName;
}



// Mapping output types

QJsonObject MappingOutput::getArticleObject() const {
    return articleObject;
}

vector<string> MappingOutput::getSourcePaths() const {
    return sourcePaths;
}
