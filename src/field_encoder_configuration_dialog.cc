#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QDialogButtonBox>
#include "field_encoder_configuration_dialog.hh"
#include "field_encoder.hh"

using std::map;
using std::string;


FieldEncoderConfigurationDialog::FieldEncoderConfigurationDialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *grid = new QGridLayout;

    grid->addWidget(createFirstGroup(), 0, 0);
    grid->addWidget(createSecondGroup(), 1, 0);
    grid->addWidget(createThirdGroup(), 2, 0);
    grid->addWidget(makeControls(), 3, 0);

    setLayout(grid);
    setWindowTitle("Field encoder configuration");
}

QWidget* FieldEncoderConfigurationDialog::makeControls()  {
    // Standard-ass buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    return buttonBox;
}

QGroupBox *FieldEncoderConfigurationDialog::createFirstGroup()
{
    QGroupBox *groupBox = new QGroupBox("Target field");

    QRadioButton *radio1 = new QRadioButton("Standard field");
    QRadioButton *radio2 = new QRadioButton("Custom field");

    radio1->setChecked(true);

    QWidget* container = new QWidget;
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    container->setLayout(vbox);

    QLineEdit* targetFieldName = new QLineEdit;
    QLabel* label = new QLabel("Target field name:");
    label->setBuddy(targetFieldName);


    QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addWidget(container);
    hbox->addWidget(label);
    hbox->addWidget(targetFieldName);

    groupBox->setLayout(hbox);
    return groupBox;
}

QGroupBox* FieldEncoderConfigurationDialog::createSecondGroup()
{
    QGroupBox *groupBox = new QGroupBox("Field encoder");
    QVBoxLayout *vbox = new QVBoxLayout;

    this->fieldEncoderList = new QListView;
    QStringList stringList = {
        "string",
        "listOfObjects",
        "lookupList",
        "contributeFiles",
    };

    QAbstractItemModel* fieldEncoderModel = new QStringListModel(stringList);
    this->fieldEncoderList->setModel(fieldEncoderModel);

    QPushButton* advancedButton = new QPushButton("Advanced...");

    connect(
        advancedButton,
        &QAbstractButton::clicked,
        this,
        &FieldEncoderConfigurationDialog::showDialog
    );

    vbox->addWidget(fieldEncoderList);
    vbox->addWidget(advancedButton);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox *FieldEncoderConfigurationDialog::createThirdGroup()
{
    QGroupBox *groupBox = new QGroupBox("Validation");
    groupBox->setCheckable(true);
    groupBox->setChecked(true);  /// change me

    QListView* validatorList = new QListView;
    QStringList stringList = {
        "url",
        "reasonableSize"
    };

    QStringListModel* model = new QStringListModel(stringList);
    validatorList->setModel(model);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(validatorList);
    groupBox->setLayout(vbox);

    return groupBox;
}


void FieldEncoderConfigurationDialog::showDialog() {
    qDebug() << "I would show dialog";
    QModelIndex theIndex = this->fieldEncoderList->currentIndex();
    string selectedFieldEncoder = theIndex.data().toString().toStdString();

    map<string, FieldEncoder&> fieldEncoders;

    ListOfObjectFieldEncoder encoder;
    FieldEncoder& genericEncoder = encoder;

    fieldEncoders.insert({"string", genericEncoder});
    fieldEncoders.insert({"listOfObjects", genericEncoder});
    fieldEncoders.insert({"lookupList", genericEncoder});
    fieldEncoders.insert({"contributeFiles", genericEncoder});


    FieldEncoder& outOfMap = fieldEncoders.at(selectedFieldEncoder);

    qDebug() << "Pulled field encoder out of map";
    qDebug() << "address is" << &outOfMap;

    QDialog* dialog = outOfMap.makeConfigurationDialog(this);
    dialog->show();
    QJsonValue json = outOfMap.asJson();

    qDebug() << "serialization is" << json;
    qDebug() << "index is" << theIndex;
}
