#include <QDebug>
#include <QMenu>
#include <QInputDialog>
#include "options_editor_view.hh"

OptionsEditorView::OptionsEditorView(
    OptionsEditorModel* optionsEditorModel, QWidget* parent
): QTableView(parent), optionsEditorModel(optionsEditorModel) {
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


    QAction* insertAction = new QAction("Insert", this);
    menu->addAction(insertAction);
    connect(
        insertAction, &QAction::triggered, [=](bool) {
            QString result = QInputDialog::getText(
                this,
                "Option name",
                "Enter the name of the new option."
            );
            
            optionsEditorModel->addOption(result.toStdString());
        }
    );

    menu->exec(event->globalPos());
}
