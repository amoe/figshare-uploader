#ifndef PRESENTER_HH
#define PRESENTER_HH

#include "driver.hh"
#include "interfaces.hh"

class PresenterImpl : public Presenter {
public:
    PresenterImpl(Driver* driver, TokenStore* tokenStore) 
        : driver(driver), tokenStore(tokenStore) {
        // This member variable needs to be initialized by a later call to 
        // setView.
        this->view = NULL;
        this->progressReporter = NULL;
    }

    void startUpload();
    void uploadFinished(string value);
    void setView(View* view);
    void fatalError(string what);
    void pickFile();
    void initializeView();
    void showAboutDialog();

private:
    View* view;
    Driver* driver;
    TokenStore* tokenStore;
    ViewProgressAdapter* progressReporter;
};

#endif
