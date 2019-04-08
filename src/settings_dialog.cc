#include <QDebug>
#include <QStringList>
#include <QStringListModel>
#include "settings_dialog.hh"
#include "field_encoder_list_view.hh"
#include "mapping_table_widget.hh"

SettingsDialog::SettingsDialog(QWidget* parent): QTabWidget(parent) {
    QStringList stringList = {"fry", "bender", "leela"};
    QStringListModel* theModel = new QStringListModel(stringList);

    MappingTableWidget* mappingTable = new MappingTableWidget(this, theModel);
    FieldEncoderListView* fieldEncoderList = new FieldEncoderListView(this, theModel);

    addTab(mappingTable, "Field mapping");
    addTab(fieldEncoderList, "Encoder configuration");
}
