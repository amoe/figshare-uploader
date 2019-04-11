#include <iostream>
#include "mapping_engine.hh"
#include "converter_registry.hh"

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
        
        ConverterName converterName = fieldEncoder.getConverterName();

        IntermediateMappingOutput result = ConverterRegistry::convert(
            converterName, value, fieldEncoder.getOptions()
        );

    }

    return MappingOutput(resultObject, resultPaths);
}
