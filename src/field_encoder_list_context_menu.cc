#include "field_encoder_list_context_menu.hh"

FieldEncoderListContextMenu::FieldEncoderListContextMenu(QModelIndex modelIndex, QWidget* parent): QMenu(parent) {
    QAction* editAction = new QAction("Edit", this);
    QAction* deleteAction = new QAction("Delete", this);

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


    addAction(editAction);
    addAction(deleteAction);
}
