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
    Q_UNUSED(option);
    Q_UNUSED(index);

    qDebug() << "Creating editor";
    qDebug() << "Parent is" << parent;

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

    qDebug() << "Setting editor data on " << comboBox;

    int row = index.row();
    int column = index.column();

    qDebug() << "The index was specified as " << row << ", " << column;

    
    QString currentText = index.data(Qt::EditRole).toString();

    int cbIndex = comboBox->findText(currentText);
    
    if (cbIndex >= 0) 
        comboBox->setCurrentIndex(cbIndex);

    // ???  we need to set the value of the combo box here
//    QStyledItemDelegate::setEditorData(editor, index);    
}


void ComboBoxItemDelegate::updateEditorGeometry(
    QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index
) const {
    // qDebug() << "Updating editor geometry";
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

void ComboBoxItemDelegate::setModelData(
    QWidget* editor, QAbstractItemModel* model, const QModelIndex& index
) const {
    qDebug() << "Setting model data";
//    QStyledItemDelegate::setModelData(editor, model, index);

    QComboBox* comboBox = getComboBox(editor);

    // This is the problem line.  Original example is from QTableWidget
    // model->setData isn't doing what it needs to.
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}

