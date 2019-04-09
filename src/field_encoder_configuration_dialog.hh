#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QListView>
#include <QGroupBox>
#include <QDialog>

class FieldEncoderConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    FieldEncoderConfigurationDialog(QWidget *parent = nullptr);
    
public slots:
    void showDialog();

private:
    QGroupBox *createFirstGroup();
    QGroupBox *createSecondGroup();
    QGroupBox *createThirdGroup();
    QWidget* makeControls();

    QListView* fieldEncoderList;
};

#endif
