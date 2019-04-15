#include <QDebug>
#include "field_encoder_model.hh"

FieldEncoderModel::FieldEncoderModel() {
    QStringList available = {"foo", "bar", "baz"};
    this->innerModel = new QStringListModel(available);
}

Qt::ItemFlags FieldEncoderModel::flags(const QModelIndex& index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

int FieldEncoderModel::rowCount(const QModelIndex& parent) const {
    return this->innerModel->rowCount(parent);
}

int FieldEncoderModel::columnCount(const QModelIndex& parent) const {
    return this->innerModel->columnCount(parent);
}

QVariant FieldEncoderModel::data(const QModelIndex& index, int role) const {
    // convert the model index request back to coordinates relative to the inner model
    QModelIndex innerIndex(innerModel->index(index.row(), index.column()));
    return this->innerModel->data(innerIndex, role);
}

QVariant FieldEncoderModel::headerData(int section, Qt::Orientation orientation, int role) const {
    return this->innerModel->headerData(section, orientation, role);
}

QModelIndex FieldEncoderModel::index(int row, int column, const QModelIndex& parent) const {
    if (parent.isValid()) {
        // There can never be a parent, because we are not a treemodel.
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex FieldEncoderModel::parent(const QModelIndex& child) const {
    return this->innerModel->parent(child);
}

