#include <iterator>
#include <QDebug>
#include "options_editor_model.hh"
#include "optional.hpp"

using nonstd::optional;
using nonstd::nullopt;

OptionsEditorModel::OptionsEditorModel(OptionsMap& options, QObject* parent):
    QAbstractTableModel(parent), options(options) {
    reIndex();
}


int OptionsEditorModel::rowCount(
    const QModelIndex &parent
) const {
    return options.size();
}

int OptionsEditorModel::columnCount(
    const QModelIndex &parent
) const {
    return 3;
}

QVariant OptionsEditorModel::data(
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
        default:
            return QVariant();
    }
}

QVariant OptionsEditorModel::headerData(
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
bool OptionsEditorModel::setData(const QModelIndex& index, const QVariant& value, int role) {

    int row = index.row();
    int column = index.column();

    string keyForRow = keyOrdering.at(row);
    optional<string> theOptional = options.at(keyForRow);

    qDebug() << "setdata called for column" << column;
    qDebug() << "role was" << role;
    qDebug() << "value was" << value;

    switch (column) {
        case OPTION_NAME:
            // Can't happen because the flag is never set
            return false;
        case HAS_VALUE:
            toggleOptional(row);
            // Invalidate ourselves and the column next to us!
            emit dataChanged(index, this->index(row, column + 1));
            return true;
        case OPTION_VALUE:
            options.at(keyForRow) = optional<string>(
                value.toString().toStdString()
            );
            return true;
        default:
            return false;
    }
}

Qt::ItemFlags OptionsEditorModel::flags(const QModelIndex& index) const {
    // Don't use the superclass method.
    Qt::ItemFlags baseFlags = Qt::NoItemFlags;

    int row = index.row();

    // Do a bounds check.
    // This shouldn't really ever happen, but for some reason it can.
    vector<string>::size_type s = row;
    if (s >= keyOrdering.size()) 
        return baseFlags;

    optional<string> theOptional = options.at(keyOrdering.at(row));

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

void OptionsEditorModel::toggleOptional(int row) {
    string keyForRow = keyOrdering.at(row);

    optional<string> theOptional = options.at(keyForRow);
    
    if (theOptional.has_value()) {
        options.at(keyForRow) = nullopt;
    } else {
        options.at(keyForRow) = optional<string>("");
    }
}


bool OptionsEditorModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, (row + count) - 1);
    qDebug() << "I would remove rows";
    qDebug() << "requested row is " << row;

    for (int i = 0; i < count; i++) {
        int effectiveIndex = row + i;
        qDebug() << "attempting index" << effectiveIndex;
        qDebug() << "key ordering size" << keyOrdering.size();

        for (string k: keyOrdering) {
            qDebug() << QString::fromStdString(k);
        }

        string key = keyOrdering.at(effectiveIndex);
        qDebug() << "key is" << QString::fromStdString(key);

        options.erase(options.find(key));
    }

    reIndex();
    endRemoveRows();
    return true;
}


QVariant OptionsEditorModel::handleDisplayRole(int row, int column) const {
    string keyForRow = keyOrdering.at(row);
    optional<string> theOptional = options.at(keyOrdering.at(row));

    switch (column) {
        case OPTION_NAME:
            return QVariant(QString::fromStdString(keyForRow));
        case HAS_VALUE:
            return QVariant();
        case OPTION_VALUE:
            return QVariant(QString::fromStdString(theOptional.value_or("NULL")));
        default:
            return QVariant();
    }
}


void OptionsEditorModel::reIndex() {
    keyOrdering.clear();

    for (const auto& pair: options) {
        string key = pair.first;
        keyOrdering.push_back(key);
    }
}

void OptionsEditorModel::addOption(string result) {
    beginInsertRows(QModelIndex(), options.size(), options.size());
    options.insert({result, nullopt});
    reIndex();
    endInsertRows();
}
