#include <QLabel>
#include <QGridLayout>
#include <QTableView>
#include "field_mapping_table_model.hh"
#include "mapping_table_widget.hh"
#include "combo_box_item_delegate.hh"

MappingTableWidget::MappingTableWidget(QWidget* parent, QAbstractItemModel* fieldEncoderModel): QWidget(parent) {
    this->fieldEncoderModel = fieldEncoderModel;
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(makeFirstGroup(), 0, 0);
    setLayout(grid);
    setWindowTitle("Mapping configuration");
}

QWidget* MappingTableWidget::makeFirstGroup() {
    QWidget* group = new QWidget(this);

    QLabel* label = new QLabel("Hello, world!", group);
    QTableView* table = new QTableView(this);

    FieldMappingTableModel* model = new FieldMappingTableModel;
    table->setModel(model);

    ComboBoxItemDelegate* delegate = new ComboBoxItemDelegate(table, this->fieldEncoderModel);
    table->setItemDelegateForColumn(0, delegate);

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(label);
    vbox->addWidget(table);
    group->setLayout(vbox);

    return group;
}
