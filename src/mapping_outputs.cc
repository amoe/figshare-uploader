#include "mapping_outputs.hh"

QJsonObject MappingOutput::getArticleObject() const {
    return articleObject;
}

vector<string> MappingOutput::getSourcePaths() const {
    return sourcePaths;
}
