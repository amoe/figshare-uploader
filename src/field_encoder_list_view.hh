#ifndef FIELD_ENCODER_LIST_VIEW_HH
#define FIELD_ENCODER_LIST_VIEW_HH

#include <QWidget>
#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
#include <QAbstractItemModel>
#include "field_encoder_model.hh"
#include "field_encoder_configuration_dialog.hh"

class FieldEncoderListView: public QWidget {
    Q_OBJECT

public:
    FieldEncoderListView(FieldEncoderModel* theModel, QWidget* parent);
    void contextMenuEvent(QContextMenuEvent* event) override;

signals:
    // This is manually forwarded all the way to the View.
    void fieldEncoderDialogConfirmed(FieldEncoderDTO data);

public slots:
    void triggerNew();
    void triggerEdit(QModelIndex index);
    void deleteItem(QModelIndex index);
    void forwardDialogConfirmedSignal(FieldEncoderDTO dto);

private:
    QListView* listView;
    
    //QAbstractItemModel* theModel;
    FieldEncoderModel* theModel;
};


#endif /* FIELD_ENCODER_LIST_VIEW_HH */
