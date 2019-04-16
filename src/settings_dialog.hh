#ifndef SETTINGS_DIALOG_HH
#define SETTINGS_DIALOG_HH

#include <string>
#include <vector>
#include <QWidget>
#include <QDialog>
#include "field_encoder_configuration_dialog.hh"

using std::string;
using std::vector;

class SettingsDialog: public QDialog {
    Q_OBJECT

public:
    SettingsDialog(
        QAbstractItemModel* fieldMappingModel,
        QAbstractItemModel* fieldEncoderModel,
        QWidget* parent
    );
    QSize sizeHint() const;

signals:
    // This is manually forwarded all the way to the View.
    void fieldEncoderDialogConfirmed(FieldEncoderDTO data);
};

#endif /* SETTINGS_DIALOG_HH */
