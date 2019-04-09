#ifndef SETTINGS_DIALOG_HH
#define SETTINGS_DIALOG_HH

#include <string>
#include <vector>
#include <QWidget>
#include <QDialog>

using std::string;
using std::vector;

class SettingsDialog: public QDialog {
public:
    SettingsDialog(QWidget* parent, vector<string> headerFields);
    QSize sizeHint() const;
};

#endif /* SETTINGS_DIALOG_HH */
