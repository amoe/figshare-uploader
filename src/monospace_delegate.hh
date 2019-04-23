#ifndef MONOSPACE_DELEGATE_HH
#define MONOSPACE_DELEGATE_HH

#include <QStyledItemDelegate>

class MonospaceDelegate: public QStyledItemDelegate {
    Q_OBJECT

public:
    MonospaceDelegate(QObject* parent): QStyledItemDelegate(parent) { }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
        const override;

    QWidget* createEditor(
        QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index
    ) const override;
    void setEditorData(
        QWidget* editor, const QModelIndex& index
    ) const override;
    void updateEditorGeometry(
        QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index
    ) const override;
    void setModelData(
        QWidget* editor, QAbstractItemModel* model, const QModelIndex& index
    ) const override;
};

#endif /* MONOSPACE_DELEGATE_HH */


