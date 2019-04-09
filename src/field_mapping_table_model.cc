#include <QDebug>
#include <string>
#include <vector>
#include "field_mapping_table_model.hh"

using std::string;
using std::vector;

FieldMappingTableModel::FieldMappingTableModel(vector<string> availableFields, QObject* parent): QAbstractTableModel(parent) {
    this->availableFields = availableFields;
    chosenMappers.resize(availableFields.size());
}


int FieldMappingTableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return availableFields.size();
}

int FieldMappingTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant FieldMappingTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return QString::fromStdString(chosenMappers.at(index.row()));
    } else {
        return QVariant();
    }
}

QVariant FieldMappingTableModel::headerData(
    int section, Qt::Orientation orientation, int role
) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    vector<string> headers = {
        "Field encoder"
    };

    if (orientation == Qt::Horizontal) {
        return QString::fromStdString(headers.at(section));
    } else {
        return QString::fromStdString(availableFields.at(section));
    }
}

bool FieldMappingTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    Q_UNUSED(role);

    qDebug() << "called to set data in model, received value" << value;

    // XXX: Here we actually need to *do something* -- but what??
    // The combo box needs to know about all options.  The model only needs to
    // know the selected option?
    chosenMappers.at(index.row()) = value.toString().toStdString();

    return true;
}

Qt::ItemFlags FieldMappingTableModel::flags(const QModelIndex& index) const {
    Q_UNUSED(index);
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
