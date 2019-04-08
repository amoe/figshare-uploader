#include <iostream>
#include <exception>
#include "presenter.hh"
#include "settings.hh"
#include "logging.hh"
#include "slot_adapter.hh"
#include "run_upload_task.hh"

using std::string;

void PresenterImpl::setView(View* view) {
    this->view = view;

    // By doing this here we install the progress adapter inside the driver.
    // When the driver runs, it will know to call back to the progress adapter,
    // which will then emit a signal that is handled by the GUI thread.
    // We also instruct the view to bind to the signal.
    
    this->progressReporter = new ViewProgressAdapter();
    driver->setProgressReporter(progressReporter);
    view->setProgressReporter(progressReporter);
}

void PresenterImpl::initializeView() {
    debugf("initializing view");

    view->setToken(Settings::getTokenOrEmpty());
}

void PresenterImpl::startUpload() {
    try {
        // This actually isn't going to work because this exception handler
        // doesn't live in the same thread.
        debugf("presenter slot was called");

        // This token will now be used by everything, because everything else
        // holds a reference to it.
        string token = view->getToken();
        tokenStore->setToken(token);
        Settings::setToken(token);

        string inputFile = view->getSelectedFile();
        debugf("value of text input is %s", view->getSelectedFile().c_str());

        StringAdapter adapter(this, &Presenter::uploadFinished);
        StringAdapter errorAdapter(this, &Presenter::fatalError);


        // XXX: malloc
        RunUploadTask* task = new RunUploadTask(
            driver, adapter, errorAdapter, inputFile
        );

        // By this stage, the token has already been initialized.
        task->run();
    // exceptions aren't polymorphic so we have to catch both
    } catch (std::runtime_error e) {
        debugf("caught std-exception in gui thread handler: %s", e.what());
    } catch (std::exception e) {
        debugf("caught runtime-exception in gui thread handler: %s", e.what());
    }
}

void PresenterImpl::uploadFinished(string value) {
    debugf("upload was finished: %s", value.c_str());
}

void PresenterImpl::fatalError(string what) {
    view->reportError(what);
}

void PresenterImpl::pickFile() {
    debugf("file pick requested");
    view->showFileDialog();
    view->addLog("Ready to upload.");
}

void PresenterImpl::showAboutDialog() {
    debugf("about dialog requested");
    view->showAboutDialog();
}

void PresenterImpl::showSettingsDialog() {
    debugf("requested to show settings dialog");
}
