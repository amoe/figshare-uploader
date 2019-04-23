#ifndef VIEW_HH
#define VIEW_HH

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include "field_mapping_table_model.hh"
#include "interfaces.hh"
#include "progress_reporter.hh"
#include "version.hh"
#include "field_encoder_configuration_dialog.hh"
#include "field_encoder_model.hh"
#include "qt_dto.hh"
#include "default_field_encoders.hh"
#include "converter_list_model.hh"

using std::string;
using std::vector;

class ViewImpl : public QMainWindow, public View {
    Q_OBJECT

public:
    ViewImpl(Presenter* presenter);

    std::string getSelectedFile();
    std::string getToken();
    void setToken(std::string newToken);
    void addLog(std::string logText);
    void reportError(std::string errorText);
    bool showFileDialog();
    void showAboutDialog();
    void setProgressReporter(ViewProgressAdapter* reporter);
    void setSourceFile(std::string sourceFile);
    void setAvailableEncoders(vector<FieldEncoder>& availableEncoders);
    void showSettingsDialog(
        vector<string> headerFields, const MappingScheme& fieldMappings,
        const ConverterRegistry& converterRegistry
    );


private slots:
    void addQLog(QString logText);
    void onMappingEncoderSetOperation(qt_dto::MappingEncoderSetOperation dto);
    void onFieldEncoderConfigurationDialogConfirmed(
        qt_dto::FieldEncoderConfigurationOperation dto
    );
    void onSaveFieldMappingsRequested();
    void onLoadFieldMappingsRequested();

private:
    Presenter* presenter;
    QLineEdit* selectedFile;
    QLineEdit* token;
    QPushButton* actionButton;
    QPlainTextEdit* logger;
    ViewProgressAdapter* reporter;
    FieldMappingTableModel* fieldMappingModel;
    FieldEncoderModel* fieldEncoderModel;
    ConverterListModel* converterListModel;
};

#endif // VIEW_HH
