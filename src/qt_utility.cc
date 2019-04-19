#include "qt_utility.hh"

namespace qt_utility {
    void popEditors(QAbstractItemModel* model, QAbstractItemView* view) {
        for (int i = 0; i < model->rowCount(); i++) {
            for (int j = 0; j < model->columnCount(); j++) {
                QModelIndex index = model->index(i, j, QModelIndex());
                view->openPersistentEditor(index);
            }
        }
    }
}
