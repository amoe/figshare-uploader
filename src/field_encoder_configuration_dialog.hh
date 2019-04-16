#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QListView>
#include <QGroupBox>
#include <QDialog>
#include <QButtonGroup>

struct FieldEncoderDTO {
    int targetFieldTypeId;
    QString fieldName;
    QModelIndex selectedConverter;
    QModelIndexList selectedValidationRules;
};

class FieldEncoderConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    FieldEncoderConfigurationDialog(QWidget *parent = nullptr);

signals:
    // This is manually forwarded all the way to the View.
    void dialogConfirmed(FieldEncoderDTO data);
    
public slots:
    void showDialog();
    void accept();

private:
    QGroupBox *createFirstGroup();
    QGroupBox *createSecondGroup();
    QGroupBox *createThirdGroup();
    QWidget* makeControls();

    QListView* converterList;
    QListView* validatorList;
    QButtonGroup* targetFieldTypeGroup;
    QLineEdit* targetFieldName;
};

#endif
