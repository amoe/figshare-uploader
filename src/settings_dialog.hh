#ifndef SETTINGS_DIALOG_HH
#define SETTINGS_DIALOG_HH

#include <QWidget>
#include <QDialog>

class SettingsDialog: public QDialog {
public:
    SettingsDialog(QWidget* parent = nullptr);
    QSize sizeHint() const;
};

#endif /* SETTINGS_DIALOG_HH */
