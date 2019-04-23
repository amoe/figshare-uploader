#include <iterator>
#include <QDebug>
#include "link_demo_model.hh"



int LinkDemoModel::rowCount(
    const QModelIndex &parent
) const {
    return options.size();
}

int LinkDemoModel::columnCount(
    const QModelIndex &parent
) const {
    return 3;
}

QVariant LinkDemoModel::data(
    const QModelIndex &index,
    int role
) const {
    int row = index.row();
    int column = index.column();

    optional<string> theOptional = getRow(row).second;

    switch (role) {
        case Qt::DisplayRole:
            if (column == OPTION_VALUE) {
                if (theOptional.has_value()) {
                    // return the real data
                    return QVariant("FOO");
                } else {
                    return QVariant();
                }
            } else {
                return QVariant();
            }
            break;
        case Qt::CheckStateRole:
            if (column == HAS_VALUE) {
                return QVariant(theOptional.has_value());
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
        case HAS_VALUE:
            // Invert the value of the boolean
            //personData.at(row).hasName = !personData.at(row).hasName;
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
    optional<string> theOptional = getRow(row).second;

    switch (index.column()) {
        case HAS_VALUE:
            return baseFlags | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
            break;
        case OPTION_VALUE:
            if (theOptional.has_value()) {
                return baseFlags | Qt::ItemIsEnabled | Qt::ItemIsEditable;
            } else {
                return baseFlags;
            }
        default:
            return baseFlags;
            break;
    }
}


pair<string, optional<string>> LinkDemoModel::getRow(int row) const {
    using iter_t = OptionsMap::const_iterator;
    iter_t iter = options.begin();
    advance(iter, row);
    return *iter;
}
