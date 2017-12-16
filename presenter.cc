#include <iostream>
#include "presenter.hh"
#include "logging.hh"
#include "expensive_operation.hh"

void PresenterImpl::someSlot() {
    debugf("presenter slot was called");

    std::string file = view->getSelectedFile();
    debugf("value of text input is %s", view->getSelectedFile().c_str());

    // ExpensiveOperation* operation = new ExpensiveOperation(this);

    // connect(
    //     operation, &ExpensiveOperation::resultReady,
    //     this, &UploadProcessLifecycle::onOperationFinished
    // );
    // operation->start();

}
