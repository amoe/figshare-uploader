#include <QTabWidget>
#include <QStringList>
#include <QStringListModel>
#include <QVBoxLayout>
#include "settings_dialog.hh"
#include "field_encoder_list_view.hh"
#include "mapping_table_widget.hh"

SettingsDialog::SettingsDialog(QWidget* parent): QDialog(parent) {
    QTabWidget* container = new QTabWidget(this);
        
    QStringList stringList = {"fry", "bender", "leela"};
    QStringListModel* theModel = new QStringListModel(stringList);

    MappingTableWidget* mappingTable = new MappingTableWidget(this, theModel);
    FieldEncoderListView* fieldEncoderList = new FieldEncoderListView(this, theModel);

    container->addTab(mappingTable, "Field mapping");
    container->addTab(fieldEncoderList, "Encoder configuration");

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->addWidget(container);
    
    this->setLayout(dialogLayout);
}
