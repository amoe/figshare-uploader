#include "field_encoder_list_context_menu.hh"

FieldEncoderListContextMenu::FieldEncoderListContextMenu(QModelIndex modelIndex, QWidget* parent): QMenu(parent) {
    this->modelIndex = modelIndex;

    // Laboriously construct the edit action
    QAction* editAction = new QAction("Edit", this);
    QAction* deleteAction = new QAction("Delete", this);

    connect(
        deleteAction,
        &QAction::triggered,
        this,
        &FieldEncoderListContextMenu::forwardBlah
    );

//        [=]( const QString &newValue ) { receiver->updateValue( "senderValue", newValue ); }

    addAction(editAction);
    addAction(deleteAction);
}


void FieldEncoderListContextMenu::forwardBlah(bool checked) {
    emit deleteRequested(modelIndex);
}

