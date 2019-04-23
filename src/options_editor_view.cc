#include <QDebug>
#include <QMenu>
#include "options_editor_view.hh"
#include "qt_utility.hh"

OptionsEditorView::OptionsEditorView(QWidget* parent): QTableView(parent) {
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void OptionsEditorView::contextMenuEvent(QContextMenuEvent *event) {
    qDebug() << "received context menu event for options editor";
    QModelIndex index = indexAt(event->pos());
    qDebug() << "index is" << index;
    QMenu* menu = new QMenu(this);
    QAction* deleteAction = new QAction("Delete", this);
    menu->addAction(deleteAction);

    connect(
        deleteAction, &QAction::triggered, [=](bool) {
            model()->removeRows(index.row(), 1);
        }
    );
    menu->exec(event->globalPos());
}
