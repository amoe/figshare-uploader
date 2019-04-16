#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QListView>
#include <QGroupBox>
#include <QDialog>
#include <QButtonGroup>

struct FieldEncoderDTO {
    FieldEncoderDTO() { val = 42; }

    int val;
};

class FieldEncoderConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    FieldEncoderConfigurationDialog(QWidget *parent = nullptr);

signals:
    void dialogConfirmed(FieldEncoderDTO data);
    
public slots:
    void showDialog();
    void accept();

private:
    QGroupBox *createFirstGroup();
    QGroupBox *createSecondGroup();
    QGroupBox *createThirdGroup();
    QWidget* makeControls();

    QListView* fieldEncoderList;
    QButtonGroup* targetFieldTypeGroup;
};

#endif
