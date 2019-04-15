#include <QMenu>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringListModel>
#include <QDebug>
#include "slot_adapter.hh"
#include "field_encoder_list_view.hh"
#include "field_encoder_configuration_dialog.hh"
#include "field_encoder_model.hh"

FieldEncoderListView::FieldEncoderListView(
    QAbstractItemModel* theModel, QWidget* parent
): QWidget(parent) {
    QVBoxLayout* vbox = new QVBoxLayout(this);
    this->setLayout(vbox);


    QLabel* help1 = new QLabel("Available field encoders are listed below.", this);
    vbox->addWidget(help1);
    QLabel* help2 = new QLabel("A field encoder defines a way to convert from an Excel field to a field in Figshare.", this);
    vbox->addWidget(help2);


    listView = new QListView(this);

    listView->setModel(theModel);
    vbox->addWidget(listView);

    this->contextMenu = makeContextMenu();
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
    this->contextMenu->exec(event->globalPos());
}


QMenu* FieldEncoderListView::makeContextMenu() {
    QMenu* result = new QMenu(this);

    // Laboriously construct the edit action
    QAction* editAction = new QAction("Edit", this);

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
