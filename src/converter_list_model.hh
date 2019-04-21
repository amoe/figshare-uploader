#ifndef CONVERTER_LIST_MODEL_HH
#define CONVERTER_LIST_MODEL_HH

#include <memory>
#include <QAbstractListModel>
#include "converter_registry.hh"

using std::unique_ptr;

class ConverterListModel: public QAbstractListModel {
    Q_OBJECT

public:
    ConverterListModel(QObject* parent);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    static vector<string> getSerializableNames();

private:
    vector<string> serializableNames;
};


#endif /* CONVERTER_LIST_MODEL_HH */
