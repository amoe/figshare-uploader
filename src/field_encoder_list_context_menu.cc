#include "field_encoder_list_context_menu.hh"

FieldEncoderListContextMenu::FieldEncoderListContextMenu(QModelIndex modelIndex, QWidget* parent): QMenu(parent) {
    QAction* newAction = new QAction("New", this);
    QAction* editAction = new QAction("Edit", this);
    QAction* deleteAction = new QAction("Delete", this);

    connect(
        newAction, &QAction::triggered,
        [=](bool checked) {
            emit newRequested();
        }
    );

    connect(
        deleteAction, &QAction::triggered,
            [=](bool checked) {
            emit deleteRequested(modelIndex);
        }
    );

    connect(
        editAction, &QAction::triggered,
            [=](bool checked) {
            emit editRequested(modelIndex);
        }
    );


    addAction(newAction);
    addAction(editAction);
    addAction(deleteAction);
}
