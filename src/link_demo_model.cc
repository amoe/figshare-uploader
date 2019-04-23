#include <QDebug>
#include "link_demo_model.hh"

int LinkDemoModel::rowCount(
    const QModelIndex &parent
) const {
    return personData.size();
}

int LinkDemoModel::columnCount(
    const QModelIndex &parent
) const {
    return 2;
}

QVariant LinkDemoModel::data(
    const QModelIndex &index,
    int role
) const {
    int row = index.row();
    int column = index.column();

    Person person = personData.at(row);

    switch (role) {
        case Qt::DisplayRole:
            if (column == 1) {
                if (person.hasName) {
                    return QVariant(QString::fromStdString(person.name));
                } else {
                    return QVariant();
                }
            } else {
                return QVariant();
            }
            break;
        case Qt::CheckStateRole:
            if (column == 0) {
                return QVariant(person.hasName);
            } else {
                return QVariant();
            }
            break;
        default:
            return QVariant();
    }
}

QVariant LinkDemoModel::headerData(
    int section,
    Qt::Orientation orientation,
    int role
) const {
    return QVariant();
}

// Required for editable model.
bool LinkDemoModel::setData(const QModelIndex& index, const QVariant& value, int role) {

    int row = index.row();
    int column = index.column();

    bool newValue = value.toBool();

    qDebug() << "setdata called for column" << column;
    qDebug() << "role was" << role;
    qDebug() << "value was" << value;

    switch (column) {
        case 0:
            personData.at(row).hasName = !personData.at(row).hasName;
            // Invalidate ourselves and the column next to us!
            emit dataChanged(index, this->index(row, column + 1));
            return true;
        default:
            return false;
    }
}

Qt::ItemFlags LinkDemoModel::flags(const QModelIndex& index) const {
    // Don't use the superclass method.
    Qt::ItemFlags baseFlags = Qt::NoItemFlags;

    int row = index.row();
    
    switch (index.column()) {
        case 0:
            return baseFlags | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
            break;
        case 1:
            if (personData.at(row).hasName) {
                return baseFlags | Qt::ItemIsEnabled | Qt::ItemIsEditable;
            } else {
                return baseFlags;
            }
        default:
            return baseFlags;
            break;
    }
}

