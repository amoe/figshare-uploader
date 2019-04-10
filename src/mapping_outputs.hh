#ifndef MAPPING_OUTPUTS_HH
#define MAPPING_OUTPUTS_HH

#include <vector>
#include <string>
#include <QJsonObject>

using std::vector;
using std::string;

class MappingOutput {
public:
    MappingOutput(
        QJsonObject articleObject, vector<string> sourcePaths
    ): articleObject(articleObject), sourcePaths(sourcePaths) {
    }
    
    QJsonObject getArticleObject() const;
    vector<string> getSourcePaths() const;

private:
    QJsonObject articleObject;
    vector<string> sourcePaths;
};

#endif /* MAPPING_OUTPUTS_HH */
