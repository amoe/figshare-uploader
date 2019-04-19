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
    FieldEncoder theEncoder = availableEncoders.at(index.row());

    optional<TargetField> maybeField = theEncoder.getTargetField();
    string targetFieldName;

    if (maybeField.has_value()) {
        targetFieldName = maybeField.value().getName();
    } else {
        targetFieldName = "<Unknown>";
    }

    if (role == Qt::DisplayRole) {
        return QVariant(QString::fromStdString(targetFieldName));
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


bool FieldEncoderModel::removeRows(int row, int count, const QModelIndex &parent) {
    qDebug() << "would delete starting at " << row << " with count " << count;

    using it = vector<FieldEncoder>::const_iterator;
    it start = availableEncoders.begin();

    int lastIndex = row + count;
    beginRemoveRows(parent, row, lastIndex);
    availableEncoders.erase(start + row, start + lastIndex);
    endRemoveRows();

    qDebug() << "size is now " << availableEncoders.size();
}

void FieldEncoderModel::blah() {
    qDebug() << "inside model etc";
    // Shows that the change did NOT percolate.
    qDebug() << "size in FieldEncoderModel is now " << availableEncoders.size();
}
