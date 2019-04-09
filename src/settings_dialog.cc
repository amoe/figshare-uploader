#include <QTabWidget>
#include <QStringList>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QDebug>
#include <iostream>

#include "settings_dialog.hh"
#include "field_encoder_list_view.hh"
#include "mapping_table_widget.hh"

SettingsDialog::SettingsDialog(QWidget* parent, string chosenFilePath): QDialog(parent) {
    std::cout << "configured dialog for path" << chosenFilePath << std::endl;
    setWindowTitle("Settings");

    QTabWidget* container = new QTabWidget(this);
        
    QStringList stringList = {"fry", "bender", "leela"};
    QStringListModel* theModel = new QStringListModel(stringList);

    MappingTableWidget* mappingTable = new MappingTableWidget(this, theModel);
    FieldEncoderListView* fieldEncoderList = new FieldEncoderListView(this, theModel);

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

    setLayout(dialogLayout);

    // Empirically determined.  Yuck
    //resize(320, 480);
}

QSize SettingsDialog::sizeHint() const {
    return QSize(320, 480);
}
