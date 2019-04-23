#include <QDebug>
#include <QMenu>
#include "options_editor_view.hh"
#include "qt_utility.hh"

OptionsEditorView::OptionsEditorView(QWidget* parent): QTableView(parent) {
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

void OptionsEditorView::contextMenuEvent(QContextMenuEvent *event) {
    qDebug() << "received context menu event for options editor";
    QModelIndex index = qt_utility::indexOfEvent(this, event);
    QMenu* menu = new QMenu(this);
    QAction* deleteAction = new QAction("Delete", this);
    menu->addAction(deleteAction);
    menu->exec(event->globalPos());
}
