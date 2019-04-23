#ifndef LINK_DEMO_MODEL_HH
#define LINK_DEMO_MODEL_HH

#include <vector>
#include <QAbstractTableModel>
#include "person.hh"

using std::vector;

class LinkDemoModel: public QAbstractTableModel {
    Q_OBJECT

public:
    LinkDemoModel(vector<Person> personData, QObject* parent = nullptr): QAbstractTableModel(parent), personData(personData) {
    }

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
    vector<Person> personData;
};

#endif /* LINK_DEMO_MODEL_HH */
