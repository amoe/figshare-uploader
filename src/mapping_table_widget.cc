#include <QLabel>
#include <QGridLayout>
#include <QTableView>
#include <QHeaderView>
#include "field_mapping_table_model.hh"
#include "mapping_table_widget.hh"
#include "combo_box_item_delegate.hh"
#include "qt_utility.hh"

MappingTableWidget::MappingTableWidget(
    QAbstractItemModel* fieldEncoderModel, QAbstractItemModel* fieldMappingModel,
    QWidget* parent
): QWidget(parent) {
    this->fieldEncoderModel = fieldEncoderModel;
    this->fieldMappingModel = fieldMappingModel;

    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(16);
    grid->addWidget(makeFirstGroup(), 0, 0);
    setWindowTitle("Mapping configuration");

    connect(
        saveButton, &QPushButton::released, this, &MappingTableWidget::saveRequested
    );

    connect(
        loadButton, &QPushButton::released, this, &MappingTableWidget::loadRequested
    );
}


QWidget* MappingTableWidget::makeFirstGroup() {
    QWidget* group = new QWidget(this);

    QLabel* label = new QLabel("Map between spreadsheet columns and field encoders.", group);
    QTableView* table = new QTableView(this);

    // This is passed in by the parent, which is the settings dialog in this
    // case.
    table->setModel(fieldMappingModel);
    ComboBoxItemDelegate* delegate = new ComboBoxItemDelegate(
        table, this->fieldEncoderModel
    );
    table->setItemDelegateForColumn(0, delegate);

    QVBoxLayout* vbox = new QVBoxLayout(group);
    vbox->addWidget(label);
    vbox->addWidget(table);

    QWidget* buttonContainer = new QWidget(this);
    QHBoxLayout* hbox = new QHBoxLayout(buttonContainer);

    loadButton = new QPushButton("Load", this);
    saveButton = new QPushButton("Save", this);

    buttonContainer->setLayout(hbox);
    hbox->addWidget(loadButton);
    hbox->addWidget(saveButton);

    vbox->addWidget(buttonContainer);


    // Fix the appearance of the table
    // popEditors is from utility.hh
    // qt_utility::popEditors(fieldMappingModel, table);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setMaximumWidth(128);

    return group;
}
