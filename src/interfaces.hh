#ifndef INTERFACES_HH
#define INTERFACES_HH

#include <string>
#include <vector>
#include "progress_reporter.hh"
#include "mapping_types.hh"
#include "domain_dto.hh"

using std::string;
using std::vector;

class View {
public:
    virtual std::string getSelectedFile() = 0;
    virtual std::string getToken() = 0;
    virtual void reportError(std::string errorText) = 0;
    virtual void addLog(std::string logText) = 0;
    virtual void showFileDialog() = 0;
    virtual void setProgressReporter(ViewProgressAdapter* reporter) = 0;
    virtual void showAboutDialog() = 0;
    virtual void showSettingsDialog(vector<string> headerFields) = 0;
    virtual void setSourceFile(std::string sourceFile) = 0;
    virtual void iterateFieldMappingModel() = 0;
    virtual void setToken(std::string newToken) = 0;
    virtual void setAvailableEncoders(vector<FieldEncoder>& availableEncoders) = 0;
};

class Presenter {
public:
    virtual void startUpload() = 0;
    virtual void uploadFinished(std::string value) = 0;
    virtual void setView(View* view) = 0;
    virtual void fatalError(std::string what) = 0;
    virtual void pickFile() = 0;
    virtual void initializeView() = 0;
    virtual void showAboutDialog() = 0;
    virtual void showSettingsDialog() = 0;
    virtual void fileConfirmed(std::string fileName) = 0;
    virtual void settingsConfirmed() = 0;

    virtual void fieldEncoderConfigurationDialogConfirmed(
        domain::FieldEncoderListOperation dto
    ) = 0;
    virtual void onMappingEncoderSetOperation(
        domain::MappingEncoderSetOperation dto
    ) = 0;

};

class Model {
public:
    virtual void setSourceFile(string newSourceFile) = 0;
    virtual vector<FieldEncoder>& getAvailableEncoders() = 0;
    virtual void addFieldEncoder(FieldEncoder f) = 0;
    virtual void bindRow(int excelRow, int fieldEncoderIndex) = 0;
    virtual void setHeaderFields(vector<string> headerFields) = 0;
    virtual const vector<string> getHeaderFields() const = 0;
    virtual const optional<string> getSourceFile() const = 0;
};

#endif // INTERFACES_HH
