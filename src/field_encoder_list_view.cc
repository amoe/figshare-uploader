#include <QWidget>
#include <QMenu>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringListModel>
#include <QDebug>
#include "slot_adapter.hh"
#include "field_encoder_list_view.hh"
#include "field_encoder_configuration_dialog.hh"
#include "field_encoder_model.hh"
#include "field_encoder_list_context_menu.hh"

FieldEncoderListView::FieldEncoderListView(
    FieldEncoderModel* theModel, QWidget* parent
): QWidget(parent) {
    this->theModel = theModel;

    QVBoxLayout* vbox = new QVBoxLayout(this);
    this->setLayout(vbox);


    QLabel* help1 = new QLabel("Available field encoders are listed below.", this);
    vbox->addWidget(help1);


    listView = new QListView(this);
    listView->setModel(theModel);
    vbox->addWidget(listView);
}

void FieldEncoderListView::contextMenuEvent(QContextMenuEvent* event) {
    qDebug() << "event happened";
    qDebug() << "list view is registered as" << listView;

    QPoint widgetPos = listView->mapFromGlobal(event->globalPos());
    QModelIndex result = listView->indexAt(widgetPos);


    if (result.isValid()) {
        // They clicked on a 'real' item
    } else {
        // They probably clicked outside of the list view
    }

    qDebug() << "model index result was" << result;

    FieldEncoderListContextMenu* thisMenu = new FieldEncoderListContextMenu(result, this);

    connect(
        thisMenu, &FieldEncoderListContextMenu::newRequested, 
        this, &FieldEncoderListView::triggerNew
    );

    connect(
        thisMenu, &FieldEncoderListContextMenu::deleteRequested, 
        this, &FieldEncoderListView::deleteItem
    );
    
    connect(
        thisMenu, &FieldEncoderListContextMenu::editRequested, 
        this, &FieldEncoderListView::triggerEdit
    );
 
    thisMenu->exec(event->globalPos());
}


void FieldEncoderListView::triggerEdit(QModelIndex index) {
    qDebug() << "I would trigger an edit";
    FieldEncoderConfigurationDialog* dialog = new FieldEncoderConfigurationDialog(
        optional<QModelIndex>(index), this
    );

    // Forward this signal
    connect(
        dialog, &FieldEncoderConfigurationDialog::fieldEncoderDialogConfirmed,
        this, &FieldEncoderListView::fieldEncoderDialogConfirmed
    );

    int result = dialog->exec();
    qDebug() << "dialog exited with result" << result;
}

void FieldEncoderListView::triggerNew() {
    qDebug() << "I would trigger a new-field-encoder dialog";
    FieldEncoderConfigurationDialog* dialog = new FieldEncoderConfigurationDialog(
        nullopt, this
    );

    // Forward this signal
    connect(
        dialog, &FieldEncoderConfigurationDialog::fieldEncoderDialogConfirmed,
        this, &FieldEncoderListView::forwardDialogConfirmedSignal
    );

    int result = dialog->exec();
    qDebug() << "dialog exited with result" << result;
}

void FieldEncoderListView::deleteItem(QModelIndex index) {
    qDebug() << "I would delete an item" << index;
    theModel->removeRow(index.row());
}

void FieldEncoderListView::forwardDialogConfirmedSignal(
    qt_dto::FieldEncoderConfigurationOperation dto
) {
    // This is a bit weird, it would be more sensible for the model to be
    // directly connected to the event, and for the model to be forwarding it.
    // But it seems to work fine.
    theModel->layoutAboutToBeChanged();
    emit fieldEncoderDialogConfirmed(dto);
    theModel->layoutChanged();
}
