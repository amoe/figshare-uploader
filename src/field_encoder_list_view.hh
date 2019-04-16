#ifndef FIELD_ENCODER_LIST_VIEW_HH
#define FIELD_ENCODER_LIST_VIEW_HH

#include <QWidget>
#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
#include <QAbstractItemModel>
#include "field_encoder_configuration_dialog.hh"

class FieldEncoderListView: public QWidget {
public:
    FieldEncoderListView(QAbstractItemModel* theModel, QWidget* parent);
    void contextMenuEvent(QContextMenuEvent* event) override;

public slots:
    void triggerNew();
    void triggerEdit(QModelIndex index);
    void deleteItem(QModelIndex index);
    void encoderDialogConfirmed(FieldEncoderDTO dto);

private:
    QListView* listView;
    QAbstractItemModel* theModel;
};


#endif /* FIELD_ENCODER_LIST_VIEW_HH */
