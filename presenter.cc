#include <iostream>
#include <exception>
#include "presenter.hh"
#include "logging.hh"
#include "slot_adapter.hh"
#include "run_upload_task.hh"

void PresenterImpl::setView(View* view) {
    this->view = view;
}

void PresenterImpl::startUpload() {
    try {
        throw std::runtime_error("something went wrong");
    // debugf("presenter slot was called");

    // std::string file = view->getSelectedFile();
    // debugf("value of text input is %s", view->getSelectedFile().c_str());

    // StringAdapter adapter(this, &Presenter::uploadFinished);

    // // XXX: malloc
    // RunUploadTask* task = new RunUploadTask(driver, adapter, file);

    // // By this stage, the token has already been initialized.
    // task->run();
        // exceptions aren't polymorphic
    } catch (std::runtime_error e) {
        debugf("caught exception: %s", e.what());
    } catch (std::exception e) {
        debugf("caught exception: %s", e.what());
    }
}

void PresenterImpl::uploadFinished(string value) {
    debugf("upload was finished: %s", value.c_str());
}
