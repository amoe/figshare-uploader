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
    SettingsDialog(QAbstractItemModel* fieldMappingModel, QWidget* parent);
    QSize sizeHint() const;
};

#endif /* SETTINGS_DIALOG_HH */
