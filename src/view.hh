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
    void showFileDialog();
    void showAboutDialog();
    void setProgressReporter(ViewProgressAdapter* reporter);
    void showSettingsDialog(vector<string> headerFields);
    void setSourceFile(std::string sourceFile);
    void iterateFieldMappingModel();
    void setAvailableEncoders(vector<FieldEncoder>& availableEncoders);
    void onFieldEncoderConfigurationDialogConfirmed(FieldEncoderDTO dto);
 
private slots:
    void addQLog(QString logText);

private:
    Presenter* presenter;
    QLineEdit* selectedFile;
    QLineEdit* token;
    QPushButton* actionButton;
    QPlainTextEdit* logger;
    ViewProgressAdapter* reporter;
    FieldMappingTableModel* fieldMappingModel;
    QAbstractItemModel* fieldEncoderModel;
};

#endif // VIEW_HH
