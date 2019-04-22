#include <QTabWidget>
#include <QStringList>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <iostream>

#include "field_mapping_table_model.hh"
#include "settings_dialog.hh"
#include "field_encoder_list_view.hh"
#include "mapping_table_widget.hh"

SettingsDialog::SettingsDialog(
    QAbstractItemModel* fieldMappingModel,
    FieldEncoderModel* fieldEncoderModel,
    QAbstractItemModel* converterListModel,
    QWidget* parent
): QDialog(parent) {
    setWindowTitle("Settings");

    // Note that the tab-widget is going to allocate horizontal and vertical
    // space for *all* of its tabs.
    // This means that if the second container is very wide and the first very
    // narrow, the first will be stretched to the width of the second.
    QTabWidget* container = new QTabWidget(this);
        
    MappingTableWidget* mappingTable = new MappingTableWidget(
        fieldEncoderModel, fieldMappingModel, this
    );
    FieldEncoderListView* fieldEncoderList = new FieldEncoderListView(
        fieldEncoderModel, converterListModel, this
    );

    connect(
        fieldEncoderList, &FieldEncoderListView::fieldEncoderDialogConfirmed,
        this, &SettingsDialog::fieldEncoderDialogConfirmed
    );

    container->addTab(mappingTable, "Field mapping");
    container->addTab(fieldEncoderList, "Encoder configuration");

    QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->addWidget(container);

    // Standard-ass buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    dialogLayout->addWidget(buttonBox);

    dialogLayout->setSpacing(16);

    setLayout(dialogLayout);
}

QSize SettingsDialog::sizeHint() const {
    return QSize(480, 480);
}
