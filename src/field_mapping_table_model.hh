#ifndef FIELD_MAPPING_TABLE_MODEL_HH
#define FIELD_MAPPING_TABLE_MODEL_HH

#include <QAbstractTableModel>
#include <vector>
#include <string>

using std::vector;
using std::string;

class FieldMappingTableModel: public QAbstractTableModel {
    Q_OBJECT

public:
    FieldMappingTableModel(vector<string> availableFields, QObject* parent = nullptr);

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

private:
    vector<string> availableFields;
    vector<string> chosenMappers;
};

#endif /* FIELD_MAPPING_TABLE_MODEL_HH */
