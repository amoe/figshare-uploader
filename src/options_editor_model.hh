#ifndef OPTIONS_EDITOR_MODEL_HH
#define OPTIONS_EDITOR_MODEL_HH

#include <vector>
#include <QAbstractTableModel>
#include "mapping_types.hh"

using std::pair;
using std::vector;

enum OptionsMapTableModelColumn {
    OPTION_NAME,
    HAS_VALUE,
    OPTION_VALUE
};

// This class will take a copy of its constructor argument, which it will
// administer internally.  There's no way to get it to modify your own data
// structure.  Instead, you need to retrieve its internal copy once you've
// finished using it, by calling the 'getModifiedOptions' method, and sync it
// with your own store.

class OptionsEditorModel: public QAbstractTableModel {
    Q_OBJECT

public:
    OptionsEditorModel(OptionsMap& options, QObject* parent = nullptr);

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


    bool removeRows(
        int row, int count, const QModelIndex &parent = QModelIndex()
    ) override;

    void addOption(string result);
    
    OptionsMap getModifiedOptions() const;

private:
    QVariant handleDisplayRole(int row, int column) const;
    void toggleOptional(int row);
    void reIndex();
    OptionsMap options;
    vector<string> keyOrdering;
};

#endif /* OPTIONS_EDITOR_MODEL_HH */
