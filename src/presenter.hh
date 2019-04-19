#ifndef PRESENTER_HH
#define PRESENTER_HH

#include "driver.hh"
#include "model.hh"
#include "interfaces.hh"
#include "domain_dto.hh"

class PresenterImpl : public Presenter {
public:
    PresenterImpl(Model* model, Driver* driver, TokenStore* tokenStore) 
        : model(model), driver(driver), tokenStore(tokenStore) {
        // This member variable needs to be initialized by a later call to 
        // setView.
        this->view = nullptr;
        this->progressReporter = nullptr;
    }

    void startUpload();
    void uploadFinished(string value);
    void setView(View* view);
    void fatalError(string what);
    void pickFile();
    void initializeView();
    void showAboutDialog();
    void showSettingsDialog();
    void fileConfirmed(std::string fileName);
    void settingsConfirmed();
    void fieldEncoderConfigurationDialogConfirmed(
        domain::FieldEncoderListOperation dto
    );

private:
    Model* model;
    View* view;
    Driver* driver;
    TokenStore* tokenStore;
    ViewProgressAdapter* progressReporter;
};

#endif
