#ifndef COMBO_BOX_ITEM_DELEGATE_HH
#define COMBO_BOX_ITEM_DELEGATE_HH
#include <QStyledItemDelegate>
#include <QComboBox>

class ComboBoxItemDelegate: public QStyledItemDelegate {
    Q_OBJECT

public:
    ComboBoxItemDelegate(QObject* parent, QAbstractItemModel* model): QStyledItemDelegate(parent), model(model) { }

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

private:
    QComboBox* getComboBox(QWidget* editor) const;
    QAbstractItemModel* model;
};

#endif /* COMBO_BOX_ITEM_DELEGATE_HH */
