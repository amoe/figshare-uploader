#ifndef FIELD_ENCODER_LIST_VIEW_HH
#define FIELD_ENCODER_LIST_VIEW_HH

#include <QWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAbstractItemModel>

class FieldEncoderListView: public QWidget {
public:
    FieldEncoderListView(QWidget* parent, QAbstractItemModel* theModel);
    void contextMenuEvent(QContextMenuEvent *event) override;

public slots:
    void triggerEdit();

private:
    QMenu* makeContextMenu();
    QMenu* contextMenu;
};


#endif /* FIELD_ENCODER_LIST_VIEW_HH */
