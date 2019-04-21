#include <iostream>
#include <stdexcept>
#include <exception>
#include "presenter.hh"
#include "settings.hh"
#include "logging.hh"
#include "slot_adapter.hh"
#include "run_upload_task.hh"
#include "xlsx.hh"

using std::string;

// XXX: There's no real reason for these to use raw pointers, they are non-Qt.
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
    view->setAvailableEncoders(model->getAvailableEncoders());
}

void PresenterImpl::startUpload() {
    try {
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
    if (model->getSourceFile().has_value()) {
        // At this point, the source file has already been scanned.
        // We pass a reference to the field mappings stored inside the model.
        view->showSettingsDialog(
            model->getHeaderFields(),
            model->getFieldMappings()
        );
    } else {
        view->reportError("Please select an input file first.");
    }
}

void PresenterImpl::fileConfirmed(string fileName) {
    std::cout << "filename was " << fileName << std::endl;

    model->setSourceFile(fileName);

    // Because we know -- ASSUME -- that the model is a dumb memory-store,
    // we don't call additional accessor methods on the model, although we certainly
    // should.
    // i.e. -- The model might massage the value, but we assume here that it
    // doesn't.

    view->setSourceFile(fileName);
    view->addLog("Scanning sheet columns.");
    XlsxReader reader(fileName);
    vector<string> headerFields = reader.rowToString(1);
    model->setHeaderFields(headerFields);
    view->addLog("Scanned sheet headers.");
    model->dumpMappingScheme();
}


void PresenterImpl::settingsConfirmed() {
    debugf("settings confirmed");

    view->iterateFieldMappingModel();

    // MappingSchemeAccumulator acc;
    // view->iterateFieldMappingModel(acc);
    

    // Now we basically need to construct a MappingScheme inside the Model.
    // Not that clear how to do so, though.
    // A good first step would be to decide how to work out how to iterate
    // the row mappings that were defined within the settings dialog.

    // We'll need to declare methods on the View that allow us to access the
    // FieldMappingTableModel.

    // qDebug() << "dialog was accepted";
    // done(QDialog::Accepted);
    // qDebug() << "in post handler";

    // // Dump the model
    // QString result =  QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    // QDir configPath(result);
    // QString dumpPath = configPath.filePath("mapping_scheme.json");

    // QString configPrefix = configPath.path();
    // QDir dir = QDir::root();
    // qDebug() << "I would create" << configPrefix;
}

void PresenterImpl::fieldEncoderConfigurationDialogConfirmed(
    domain::FieldEncoderListOperation dto
) {
    debugf("inside presenter fieldEncoderConfigurationDialogConfirmed");

    std::cout << "Index is " << dto.index << std::endl;
    std::cout << "Field target type id is " << dto.targetFieldTypeId << std::endl;
    std::cout << "Field name is " << dto.fieldName << std::endl;
    std::cout << "Converter index is " << dto.converterIndex << std::endl;

    for (int v: dto.validationRuleIndices) {
        std::cout << "Validation rule assigned: " << v << std::endl;
    }

    // Some crap to satisfy the not-specific-enough test.

    optional<TargetField> targetField = nullopt;
    if (dto.isTargetFieldSet) {
        targetField = TargetField(
            static_cast<TargetFieldType>(dto.targetFieldTypeId),
            dto.fieldName
        );
    }

    FieldEncoder titleEncoder(
        targetField,
        static_cast<ConverterName>(dto.converterIndex),
        {},
        {}   // Not supporting passing options!
    );

    model->addFieldEncoder(titleEncoder);
}

void PresenterImpl::onMappingEncoderSetOperation(
    domain::MappingEncoderSetOperation dto
) {
    debugf("inside presenterimpl mappingencodersetoperation");

    // Take action based on what happened
    std::cout << "Excel row index was " << dto.excelRowIndex << std::endl;
    std::cout << "Field encoder index was " << dto.fieldEncoderIndex << std::endl;

    model->bindRow(dto.excelRowIndex, dto.fieldEncoderIndex);
}
