#include <QDebug>
#include "converter_list_model.hh"

ConverterListModel::ConverterListModel(QObject* parent): QAbstractListModel(parent) {
    qDebug() << "initializing converter list model";

    lookupRegistry = unique_ptr<LookupRegistry>(new LookupRegistryImpl());
}


int ConverterListModel::rowCount(const QModelIndex &parent) const {
    return 1;
}

QVariant ConverterListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        return QVariant("FOO");
    } else {
        return QVariant();
    }
}

