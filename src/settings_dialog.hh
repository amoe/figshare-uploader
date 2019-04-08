#ifndef SETTINGS_DIALOG_HH
#define SETTINGS_DIALOG_HH

#include <QWidget>
#include <QTabWidget>

class SettingsDialog: public QTabWidget {
public:
    SettingsDialog(QWidget* parent = nullptr);
};

#endif /* SETTINGS_DIALOG_HH */
