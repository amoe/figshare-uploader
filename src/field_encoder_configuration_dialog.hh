#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QListView>
#include <QGroupBox>
#include <QDialog>
#include <QButtonGroup>
#include "optional.hpp"
#include "qt_dto.hh"
#include "mapping_types.hh"
#include "options_editor_view.hh"

using nonstd::optional;
using nonstd::nullopt;

class FieldEncoderConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    FieldEncoderConfigurationDialog(
        optional<QModelIndex> editIndex,
        optional<FieldEncoder> initializingEncoder,
        QAbstractItemModel* converterListModel,
        QWidget *parent = nullptr
    );

signals:
    // This is manually forwarded all the way to the View.
    void fieldEncoderDialogConfirmed(
        qt_dto::FieldEncoderConfigurationOperation data
    );
    
public slots:
    void accept();
    void complain();

private:
    void setContent(FieldEncoder inputEncoder);
    QGroupBox *createFirstGroup();
    QGroupBox *createSecondGroup();
    QGroupBox *createThirdGroup();
    QWidget* makeControls();

    optional<QModelIndex> editIndex;
    QListView* converterList;
    QListView* validatorList;
    QButtonGroup* targetFieldTypeGroup;
    QLineEdit* targetFieldName;
    QGroupBox* targetFieldGroupBox;
    QGroupBox* converterGroupBox;
    QGroupBox* validationRulesGroupBox;
    QAbstractItemModel* converterListModel;
    OptionsEditorView* optionsEditorView;
    OptionsEditorModel* optionsEditorModel;
    OptionsMap blankMap;
};

#endif
