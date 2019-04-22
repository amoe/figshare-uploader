#ifndef FIELD_ENCODER_LIST_VIEW_HH
#define FIELD_ENCODER_LIST_VIEW_HH

#include <QWidget>
#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
#include <QAbstractItemModel>
#include "field_encoder_model.hh"
#include "field_encoder_configuration_dialog.hh"
#include "qt_dto.hh"
#include "converter_list_model.hh"

class FieldEncoderListView: public QWidget {
    Q_OBJECT

public:
    FieldEncoderListView(FieldEncoderModel* theModel, QAbstractItemModel* converterListModel, QWidget* parent);
    void contextMenuEvent(QContextMenuEvent* event) override;

signals:
    // This is manually forwarded all the way to the View.
    void fieldEncoderDialogConfirmed(
        qt_dto::FieldEncoderConfigurationOperation data
    );

public slots:
    void triggerNew();
    void triggerEdit(QModelIndex index);
    void deleteItem(QModelIndex index);
    void forwardDialogConfirmedSignal(
        qt_dto::FieldEncoderConfigurationOperation dto
    );

private:
    QListView* listView;
    
    FieldEncoderModel* theModel;
    QAbstractItemModel* converterListModel;
};


#endif /* FIELD_ENCODER_LIST_VIEW_HH */
