#include <iterator>
#include <QDebug>
#include "link_demo_model.hh"
#include "optional.hpp"

using nonstd::optional;
using nonstd::nullopt;

LinkDemoModel::LinkDemoModel(OptionsMap& options, QObject* parent):
    QAbstractTableModel(parent), options(options) {
    
    for (const auto& pair: options) {
        string key = pair.first;
        keyOrdering.push_back(key);
    }
}


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

    optional<string> theOptional = options.at(keyOrdering.at(row));

    switch (role) {
        case Qt::DisplayRole:
            return handleDisplayRole(row, column);
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
    if (orientation != Qt::Horizontal)
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
        case OPTION_NAME:
            return QVariant("Option name");
        case HAS_VALUE:
            return QVariant("Has value?");
        case OPTION_VALUE:
            return QVariant("Option value");
        default:
            return QVariant();
    }
}

// Required for editable model.
bool LinkDemoModel::setData(const QModelIndex& index, const QVariant& value, int role) {

    int row = index.row();
    int column = index.column();

    bool newValue = value.toBool();
    optional<string> theOptional = options.at(keyOrdering.at(row));

    qDebug() << "setdata called for column" << column;
    qDebug() << "role was" << role;
    qDebug() << "value was" << value;

    switch (column) {
        case HAS_VALUE:
            toggleOptional(row);
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
    optional<string>& theOptional = options.at(keyOrdering.at(row));

    switch (index.column()) {
        case OPTION_NAME:
            return baseFlags | Qt::ItemIsEnabled;
            break;
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

void LinkDemoModel::toggleOptional(int row) {
    string keyForRow = keyOrdering.at(row);

    optional<string> theOptional = options.at(keyForRow);
    
    if (theOptional.has_value()) {
        options.at(keyForRow) = nullopt;
    } else {
        options.at(keyForRow) = optional<string>("");
    }
}


bool LinkDemoModel::removeRows(int row, int count, const QModelIndex &parent) {
    return true;
}


QVariant LinkDemoModel::handleDisplayRole(int row, int column) const {
    string keyForRow = keyOrdering.at(row);
    optional<string> theOptional = options.at(keyOrdering.at(row));

    switch (column) {
        case OPTION_NAME:
            return QVariant(QString::fromStdString(keyForRow));
        case OPTION_VALUE:
            return QVariant(QString::fromStdString(theOptional.value_or("NULL")));
        default:
            return QVariant();
    }
}
