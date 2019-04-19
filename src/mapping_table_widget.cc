#include <QLabel>
#include <QGridLayout>
#include <QTableView>
#include <QHeaderView>
#include "field_mapping_table_model.hh"
#include "mapping_table_widget.hh"
#include "combo_box_item_delegate.hh"

MappingTableWidget::MappingTableWidget(
    QAbstractItemModel* fieldEncoderModel, QAbstractItemModel* fieldMappingModel,
    QWidget* parent
): QWidget(parent) {
    this->fieldEncoderModel = fieldEncoderModel;
    this->fieldMappingModel = fieldMappingModel;

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(makeFirstGroup(), 0, 0);
    setLayout(grid);
    setWindowTitle("Mapping configuration");
}

QWidget* MappingTableWidget::makeFirstGroup() {
    QWidget* group = new QWidget(this);

    QLabel* label = new QLabel("Hello, world!", group);
    QTableView* table = new QTableView(this);

    // This is passed in by the parent, which is the settings dialog in this
    // case.
    table->setModel(fieldMappingModel);

    ComboBoxItemDelegate* delegate = new ComboBoxItemDelegate(table, this->fieldEncoderModel);
    table->setItemDelegateForColumn(0, delegate);

    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(label);
    vbox->addWidget(table);
    group->setLayout(vbox);


    table->horizontalHeader()->setStretchLastSection(true);

    return group;
}
