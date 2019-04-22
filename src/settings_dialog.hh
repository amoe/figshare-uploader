#ifndef SETTINGS_DIALOG_HH
#define SETTINGS_DIALOG_HH

#include <string>
#include <vector>
#include <QWidget>
#include <QDialog>
#include "field_encoder_model.hh"
#include "field_encoder_configuration_dialog.hh"
#include "qt_dto.hh"

using std::string;
using std::vector;

class SettingsDialog: public QDialog {
    Q_OBJECT

public:
    SettingsDialog(
        QAbstractItemModel* fieldMappingModel,
        FieldEncoderModel* fieldEncoderModel,
        QAbstractItemModel* converterListModel,
        QWidget* parent
    );
    QSize sizeHint() const;

signals:
    // This is manually forwarded all the way to the View.
    void fieldEncoderDialogConfirmed(
        qt_dto::FieldEncoderConfigurationOperation data
    );
};

#endif /* SETTINGS_DIALOG_HH */
