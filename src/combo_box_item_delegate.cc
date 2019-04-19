#include <QComboBox>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QStringList>
#include <QStringListModel>
#include "combo_box_item_delegate.hh"

using std::string;
using std::vector;

QWidget* ComboBoxItemDelegate::createEditor(
    QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index
) const {
    QComboBox* comboBox = new QComboBox(parent);
    comboBox->setModel(this->model);
    
    return comboBox;
}

QComboBox* ComboBoxItemDelegate::getComboBox(QWidget* editor) const {
    QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
    Q_ASSERT(comboBox);
    return comboBox;
}

void ComboBoxItemDelegate::setEditorData(
    QWidget* editor, const QModelIndex& index
) const {
    QComboBox* comboBox = getComboBox(editor);
    int row = index.row();
    int column = index.column();
    QString currentText = index.data(Qt::EditRole).toString();
    int cbIndex = comboBox->findText(currentText);
    if (cbIndex >= 0) 
        comboBox->setCurrentIndex(cbIndex);
}


void ComboBoxItemDelegate::updateEditorGeometry(
    QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index
) const {
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

void ComboBoxItemDelegate::setModelData(
    QWidget* editor, QAbstractItemModel* model, const QModelIndex& index
) const {
    qDebug() << "Setting model data";
    QComboBox* comboBox = getComboBox(editor);
    model->setData(index, comboBox->currentIndex(), Qt::EditRole);
}

