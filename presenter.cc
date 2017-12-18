#include <iostream>
#include "presenter.hh"
#include "logging.hh"
#include "slot_adapter.hh"
#include "run_upload_task.hh"

void PresenterImpl::someSlot() {
    debugf("presenter slot was called");

    std::string file = view->getSelectedFile();
    debugf("value of text input is %s", view->getSelectedFile().c_str());

    SlotAdapter adapter(this, &Presenter::uploadFinished);

    RunUploadTask task(adapter);
    task.run();
}

void PresenterImpl::uploadFinished() {
    debugf("upload was finished");
}
