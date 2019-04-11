#include <iostream>
#include "mapping_engine.hh"

using std::cout;
using std::endl;

MappingOutput MappingEngine::convert(vector<string> document, MappingScheme scheme) {
    QJsonObject resultObject;
    vector<string> resultPaths;

    for (RowMapping r : scheme) {
        int sourceRowIndex = r.getSourceRowIndex();
        FieldEncoder fieldEncoder = r.getFieldEncoder();

        string value = document.at(sourceRowIndex);
        cout << "value is " << value << endl;
        
        ConverterName converter = fieldEncoder.getConverterName();
        // QJsonValue result = ConverterRegistry::convert(
        //     converter, fieldEncoder.getOptions()
        // );
    }

    return MappingOutput(resultObject, resultPaths);
}
