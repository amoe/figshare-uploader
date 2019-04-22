#include <QDebug>
#include <QAbstractButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "converter_list_model.hh"
#include "field_encoder_configuration_dialog.hh"
#include "field_encoder_widget.hh"

using std::map;
using std::string;

FieldEncoderConfigurationDialog::FieldEncoderConfigurationDialog(
    optional<QModelIndex> editIndex, 
    optional<FieldEncoder> initializingEncoder,
    QAbstractItemModel* converterListModel,
    QWidget *parent
) : QDialog(parent) {
    this->editIndex = editIndex;
    this->converterListModel = converterListModel;
    QGridLayout *grid = new QGridLayout;

    targetFieldGroupBox = createFirstGroup();
    converterGroupBox = createSecondGroup();
    validationRulesGroupBox = createThirdGroup();

    connect(
        validationRulesGroupBox, &QGroupBox::toggled, 
        this, &FieldEncoderConfigurationDialog::complain
    );

    grid->addWidget(targetFieldGroupBox, 0, 0);
    grid->addWidget(converterGroupBox, 1, 0);
    grid->addWidget(validationRulesGroupBox, 2, 0);
    grid->addWidget(makeControls(), 3, 0);

    setLayout(grid);
    setWindowTitle("Field encoder configuration");
    
    if (initializingEncoder.has_value())
        setContent(initializingEncoder.value());
}

void FieldEncoderConfigurationDialog::setContent(FieldEncoder inputEncoder) {
    // Handle field type
    if (inputEncoder.getTargetField().has_value()) {
        TargetField targetField = inputEncoder.getTargetField().value();
        targetFieldGroupBox->setChecked(true);

        int buttonIndex = static_cast<int>(targetField.getTargetFieldType());
        targetFieldTypeGroup->button(buttonIndex)->setChecked(true);

        targetFieldName->setText(QString::fromStdString(targetField.getName()));
    } else {
        targetFieldGroupBox->setChecked(false);
        targetFieldName->setText("");

        for (QAbstractButton* button: targetFieldTypeGroup->buttons()) {
            button->setChecked(false);
        }
    }

    // Select the correct converter
    int row = static_cast<int>(inputEncoder.getConverterName());
    converterList->setCurrentIndex(converterListModel->index(row, 0));

    // XXX: Ensure the validation rules are selected

    // XXX: Add the options to the options map
}


QGroupBox *FieldEncoderConfigurationDialog::createFirstGroup() {
    QGroupBox* groupBox = new QGroupBox("Target field");
    groupBox->setCheckable(true);

    targetFieldTypeGroup = new QButtonGroup(this);
    QRadioButton* radio1 = new QRadioButton("Standard field");
    QRadioButton* radio2 = new QRadioButton("Custom field");

    // Add buttons to group with symbolic values
    targetFieldTypeGroup->addButton(radio1, 0);
    targetFieldTypeGroup->addButton(radio2, 1);

    radio1->setChecked(true);

    QWidget* container = new QWidget;
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    container->setLayout(vbox);

    QLabel* label = new QLabel("Target field name:");
    targetFieldName = new QLineEdit(this);
    label->setBuddy(targetFieldName);

    QHBoxLayout* hbox = new QHBoxLayout;
    hbox->addWidget(container);
    hbox->addWidget(label);
    hbox->addWidget(targetFieldName);

    groupBox->setLayout(hbox);
    return groupBox;
}

QGroupBox* FieldEncoderConfigurationDialog::createSecondGroup() {
    QGroupBox* groupBox = new QGroupBox("Conversion types");
    QVBoxLayout* vbox = new QVBoxLayout;

    converterList = new QListView;
    converterList->setSelectionMode(QAbstractItemView::SingleSelection);
    converterList->setModel(converterListModel);

    QPushButton* advancedButton = new QPushButton("Advanced...");

    connect(
        advancedButton,
        &QAbstractButton::clicked,
        this,
        &FieldEncoderConfigurationDialog::showEncoderOptionsDialog
    );

    vbox->addWidget(converterList);
    vbox->addWidget(advancedButton);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox *FieldEncoderConfigurationDialog::createThirdGroup() {
    QGroupBox *groupBox = new QGroupBox("Local validation rules");
    
    groupBox->setCheckable(true);
    groupBox->setChecked(false);

    validatorList = new QListView;
    validatorList->setSelectionMode(QAbstractItemView::MultiSelection);
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

QWidget* FieldEncoderConfigurationDialog::makeControls()  {
    // Standard-ass buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel
    );

    connect(buttonBox, &QDialogButtonBox::accepted, this, &FieldEncoderConfigurationDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    return buttonBox;
}


void FieldEncoderConfigurationDialog::showEncoderOptionsDialog() {
    qDebug() << "I would show dialog";
    // FYI: THIS IS ILLEGAL AND UNDEFINED BEHAVIOUR!

    QMessageBox::critical(
        this,
        "Error",
        "FIX ME!"
    );

    
    // QModelIndex theIndex = converterList->currentIndex();
    // string selectedFieldEncoder = theIndex.data().toString().toStdString();

    // map<string, FieldEncoderWidget&> fieldEncoders;

    // ListOfObjectFieldEncoder encoder;
    // FieldEncoderWidget& genericEncoder = encoder;

    // fieldEncoders.insert({"string", genericEncoder});
    // fieldEncoders.insert({"listOfObjects", genericEncoder});
    // fieldEncoders.insert({"lookupList", genericEncoder});
    // fieldEncoders.insert({"contributeFiles", genericEncoder});

    // FieldEncoderWidget& outOfMap = fieldEncoders.at(selectedFieldEncoder);

    // qDebug() << "Pulled field encoder out of map";
    // qDebug() << "address is" << &outOfMap;

    // QDialog* dialog = outOfMap.makeConfigurationDialog(this);
    // dialog->show();
    // QJsonValue json = outOfMap.asJson();

    // qDebug() << "serialization is" << json;
    // qDebug() << "index is" << theIndex;
}

void FieldEncoderConfigurationDialog::accept() {
    // Emit our own object to transfer the data back to somewhere that it can
    // be dealt with.  We get the data out of the dialog in the most basic way
    // possible.  We want this part of the code to not contain tons of munging
    // logic.
    // This DTO will be received in FieldEncoderListView#encoderDialogConfirmed.

    qt_dto::FieldEncoderConfigurationOperation result;

    result.index = editIndex.value_or(QModelIndex());
    result.targetFieldControlsChecked = targetFieldGroupBox->isChecked();
    result.targetFieldTypeId = targetFieldTypeGroup->checkedId();
    result.fieldName = targetFieldName->text();
    result.selectedConverter = converterList->currentIndex();
    result.selectedValidationRules = validatorList->selectionModel()->selectedIndexes();

    qDebug() << "About to emit confirmation signal";
    emit fieldEncoderDialogConfirmed(result);
    done(QDialog::Accepted);
}

void FieldEncoderConfigurationDialog::complain() {
    validationRulesGroupBox->setChecked(false);
    QMessageBox::critical(
        this,
        "Error",
        "Sorry — local validation rules are not implemented yet."
    );
}
