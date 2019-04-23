#include <QDebug>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QApplication>
#include "monospace_delegate.hh"

void MonospaceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    const QWidget *widget = option.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();

    QFont font("", 10);
    font.setStyleHint(QFont::TypeWriter);
    font.setStyleStrategy(QFont::PreferAntialias);
    opt.font = font;

    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
}

QWidget* MonospaceDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void MonospaceDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
    QStyledItemDelegate::setEditorData(editor, index);    
}

void MonospaceDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}

void MonospaceDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
    QStyledItemDelegate::setModelData(editor, model, index);
}



