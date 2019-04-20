#ifndef FIELD_MAPPING_TABLE_MODEL_HH
#define FIELD_MAPPING_TABLE_MODEL_HH

#include <QAbstractTableModel>
#include <vector>
#include <string>
#include "mapping_types.hh"
#include "qt_dto.hh"

using std::vector;
using std::string;

class FieldMappingTableModel: public QAbstractTableModel {
    Q_OBJECT

public:
    FieldMappingTableModel(
        vector<string> availableFields, 
        const MappingScheme& mappingScheme,
        QObject* parent = nullptr
    );

    // Minimal set for non-editable display model.
    int rowCount(
        const QModelIndex &parent = QModelIndex()
    ) const override;
    int columnCount(
        const QModelIndex &parent = QModelIndex()
    ) const override;
    QVariant data(
        const QModelIndex &index,
        int role
    ) const override;
    QVariant headerData(
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole
    ) const override;

    // Required for editable model.
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

signals:
    void mappingEncoderSet(qt_dto::MappingEncoderSetOperation dto);

private:
    vector<string> availableFields;
    const MappingScheme& mappingScheme;
};

#endif /* FIELD_MAPPING_TABLE_MODEL_HH */
