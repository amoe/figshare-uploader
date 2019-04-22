#ifndef CONVERTER_LIST_MODEL_HH
#define CONVERTER_LIST_MODEL_HH

#include <memory>
#include <QAbstractListModel>
#include "converter_registry.hh"

using std::unique_ptr;

class ConverterListModel: public QAbstractListModel {
    Q_OBJECT

public:
    ConverterListModel(const ConverterRegistry& converterRegistry, QObject* parent);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    vector<string> getSerializableNames() const;

private:
    vector<string> serializableNames;
    const ConverterRegistry& converterRegistry;
};


#endif /* CONVERTER_LIST_MODEL_HH */
