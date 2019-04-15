#ifndef FIELD_ENCODER_LIST_CONTEXT_MENU_HH
#define FIELD_ENCODER_LIST_CONTEXT_MENU_HH

#include <QMenu>
#include <QModelIndex>

class FieldEncoderListContextMenu: public QMenu {
    Q_OBJECT
    
public:
    FieldEncoderListContextMenu(QModelIndex modelIndex, QWidget* parent);

public slots:
    void forwardBlah(bool checked);

signals:
    void deleteRequested(QModelIndex modelIndex);

private:
    QModelIndex modelIndex;
};

#endif /* FIELD_ENCODER_LIST_CONTEXT_MENU_HH */
