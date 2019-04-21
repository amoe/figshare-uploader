#include <QDebug>
#include "converter_list_model.hh"


ConverterListModel::ConverterListModel(QObject* parent): QAbstractListModel(parent) {
    qDebug() << "initializing converter list model";

    // We just assume that the converter list can never be modified during
    // program run time.
    serializableNames = getSerializableNames();
}


int ConverterListModel::rowCount(const QModelIndex &parent) const {
    return serializableNames.size();
}

QVariant ConverterListModel::data(const QModelIndex &index, int role) const {

    string requestedName = serializableNames.at(index.row());

    if (role == Qt::DisplayRole) {
        return QVariant(QString::fromStdString(requestedName));
    } else {
        return QVariant();
    }
}


vector<string> ConverterListModel::getSerializableNames() {
    ConverterNameBijectiveMapper nameMapper;
    LookupRegistryImpl lookupRegistry;
    ConverterRegistry converterRegistry(&lookupRegistry);
    vector<ConverterName> converterNames = converterRegistry.getRegisteredConverters();

    vector<string> result;
    for (ConverterName symbolicName: converterNames) {
        result.push_back(
            nameMapper.getSerializableName(symbolicName)
        );
    }

    return result;
}
