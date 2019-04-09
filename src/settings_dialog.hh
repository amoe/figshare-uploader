#ifndef SETTINGS_DIALOG_HH
#define SETTINGS_DIALOG_HH

#include <QWidget>
#include <QDialog>

using std::string;

class SettingsDialog: public QDialog {
public:
    SettingsDialog(QWidget* parent, string chosenFilePath);
    QSize sizeHint() const;
};

#endif /* SETTINGS_DIALOG_HH */
