#include <QDebug>
#include "field_encoder_model.hh"
#include "logging.hh"


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
    string encoderDescription = theEncoder.describe();

    if (role == Qt::DisplayRole) {
        return QVariant(QString::fromStdString(encoderDescription));
    } else {
        return QVariant();
    }
}

QVariant FieldEncoderModel::headerData(
    int section, Qt::Orientation orientation, int role) const {
    return QVariant();
}

QModelIndex FieldEncoderModel::index(
    int row, int column, const QModelIndex& parent) const {
    if (parent.isValid()) {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex FieldEncoderModel::parent(
    const QModelIndex& child) const
 {
    return QModelIndex();
}


bool FieldEncoderModel::removeRows(int row, int count, const QModelIndex &parent) {
    qDebug() << "would delete starting at " << row << " with count " << count;

    using it = vector<FieldEncoder>::const_iterator;
    it start = availableEncoders.begin();

    int lastIndex = row + count;
    beginRemoveRows(parent, row, (row + count) - 1);
    // XXX: Instead of modifying the reference, should probably emit a signal
    // which is handled by the view.
    availableEncoders.erase(start + row, start + lastIndex);
    endRemoveRows();

    qDebug() << "size is now " << availableEncoders.size();
    return true;
}

const FieldEncoder FieldEncoderModel::getFieldEncoderByRow(int row) const {
    spdlog::info("request for row came in: {}", row);
    spdlog::info("size of encoders array is: {}", availableEncoders.size());
    return availableEncoders.at(row);
}
