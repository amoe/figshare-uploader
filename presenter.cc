#include <iostream>
#include "presenter.hh"
#include "logging.hh"
#include "slot_adapter.hh"
#include "run_upload_task.hh"

void PresenterImpl::setView(View* view) {
    this->view = view;
}

void PresenterImpl::someSlot() {
    debugf("presenter slot was called");

    std::string file = view->getSelectedFile();
    debugf("value of text input is %s", view->getSelectedFile().c_str());

    StringAdapter adapter(this, &Presenter::uploadFinished);

    // XXX: malloc
    RunUploadTask* task = new RunUploadTask(driver, adapter);
    task->run();
}

void PresenterImpl::uploadFinished(string value) {
    debugf("upload was finished: %s", value.c_str());
}
