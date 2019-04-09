#include <QMenu>
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include <QDebug>
#include "slot_adapter.hh"
#include "field_encoder_list_view.hh"
#include "field_encoder_configuration_dialog.hh"
#include "field_encoder_model.hh"

FieldEncoderListView::FieldEncoderListView(QWidget* parent, QAbstractItemModel* theModel): QWidget(parent) {
    QVBoxLayout* vbox = new QVBoxLayout(this);
    this->setLayout(vbox);
    QLabel* hello = new QLabel("foo", this);
    vbox->addWidget(hello);

    QListView* list = new QListView(this);

    list->setModel(theModel);
    vbox->addWidget(list);

    this->contextMenu = makeContextMenu();
}

void FieldEncoderListView::contextMenuEvent(QContextMenuEvent *event) {
    qDebug() << "event happened";
    this->contextMenu->exec(event->globalPos());
}




QMenu* FieldEncoderListView::makeContextMenu() {
    QMenu* result = new QMenu(this);

    // Laboriously construct the edit action
    QAction* editAction = new QAction("Edit", this);

    // Find some way to connect the edit trigger...
    // SlotAdapter editAdapter(this, &FieldEncoderListView::triggerEdit);
    // connect(editAction, &QAction::triggered, editAdapter);

    connect(
        editAction,
        &QAction::triggered,
        this,
        &FieldEncoderListView::triggerEdit
    );

    result->addAction(editAction);

    // Then...
    result->addAction("Delete");

    return result;
}

void FieldEncoderListView::triggerEdit() {
    qDebug() << "I would trigger an edit";

    FieldEncoderConfigurationDialog* dialog = new FieldEncoderConfigurationDialog(this);
    int result = dialog->exec();
    qDebug() << "dialog exited with result" << result;
}
