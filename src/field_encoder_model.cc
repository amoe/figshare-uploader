#include <QDebug>
#include "field_encoder_model.hh"

Qt::ItemFlags FieldEncoderModel::flags(const QModelIndex& index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

int FieldEncoderModel::rowCount(const QModelIndex& parent) const {
    return availableEncoders.size();
}

int FieldEncoderModel::columnCount(const QModelIndex& parent) const {
    return 1;
}

QVariant FieldEncoderModel::data(const QModelIndex& index, int role) const {
    if (role == Qt::DisplayRole) {
        return QVariant("SOME ENCODER");
    } else {
        return QVariant();
    }
}

QVariant FieldEncoderModel::headerData(int section, Qt::Orientation orientation, int role) const {
    return QVariant();
}

QModelIndex FieldEncoderModel::index(int row, int column, const QModelIndex& parent) const {
    if (parent.isValid()) {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex FieldEncoderModel::parent(const QModelIndex& child) const {
    return QModelIndex();
}

