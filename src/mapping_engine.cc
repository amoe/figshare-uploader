#include <QDebug>
#include <QJsonDocument>
#include <QString>
#include <iostream>
#include "mapping_engine.hh"
#include "converter_registry.hh"

using std::cout;
using std::endl;

MappingOutput MappingEngine::convert(vector<string> document, MappingScheme scheme) { 
    QJsonObject resultObject;
    vector<string> resultPaths;

    MappingOutput seed(resultObject, resultPaths);

    for (RowMapping r : scheme) {
        int sourceRowIndex = r.getSourceRowIndex();
        FieldEncoder fieldEncoder = r.getFieldEncoder();

        string value = document.at(sourceRowIndex);
        cout << "value is " << value << endl;
        
        ConverterName converterName = fieldEncoder.getConverterName();

        IntermediateMappingOutput result = converterRegistry->convert(
            converterName, value, fieldEncoder.getOptions()
        );


        QJsonDocument doc(seed.getArticleObject());
        QString strJson(doc.toJson(QJsonDocument::Compact));
        qDebug() << "BEFORE: " << strJson;


        seed = fieldEncoder.applyEncoder(seed, result);

        QJsonDocument doc2(seed.getArticleObject());
        QString strJson2(doc.toJson(QJsonDocument::Compact));
        qDebug() << "AFTER: " << strJson2;

    }

    return seed;
}

