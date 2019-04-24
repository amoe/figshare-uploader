#ifndef FIELD_ENCODER_MODEL_HH
#define FIELD_ENCODER_MODEL_HH

#include <Qt>
#include <QModelIndex>
#include <QStringListModel>
#include "mapping_types.hh"

// We hold a *reference* to the piece of state that is owned by the Model 
// proper.

class FieldEncoderModel: public QAbstractItemModel {

public:
    FieldEncoderModel(
        vector<FieldEncoder>& availableEncoders
    ): availableEncoders(availableEncoders) {}

    // These methods are part of the QAbstractItemModel interface.
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    // These methods are extensions for use by collaborating classes.
    const FieldEncoder getFieldEncoderByRow(int row) const;

private:
    // presently a non-const reference, removeRows directly modifies the array
    vector<FieldEncoder>& availableEncoders;
};

#endif /* FIELD_ENCODER_MODEL_HH */
