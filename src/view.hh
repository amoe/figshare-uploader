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
 
private:
    Presenter* presenter;
    QLineEdit* selectedFile;
    QLineEdit* token;
    QPushButton* actionButton;
    QPlainTextEdit* logger;
    ViewProgressAdapter* reporter;
    FieldMappingTableModel* fieldMappingModel;
    QAbstractItemModel* fieldEncoderModel;

private slots:
    void addQLog(QString logText);
};

#endif // VIEW_HH
