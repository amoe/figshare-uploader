#include <iostream>
#include <QApplication>
#include <QSslSocket>
#include <QThread>
#include "driver.hh"
#include "figshare_gateway.hh"
#include "part_preparer.hh"
#include "file_spec_generator.hh"
#include "article_mapper.hh"
#include "view.hh"
#include "presenter.hh"
#include "logging.hh"
#include "token_store.hh"
#include "group_mapper.hh"
#include "application_metadata.hh"
#include "converter_registry.hh"
#include "mapping_engine.hh"


void dumpSslInformation() {
    qDebug() << "Supports SSL:" << QSslSocket::supportsSsl();
    qDebug() << "COMPILE TIME INFO:";
    qDebug() << "sslLibraryBuildVersionNumber:" << QSslSocket::sslLibraryBuildVersionNumber();
    qDebug() << "sslLibraryBuildVersionString:" << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "RUN TIME INFO:";
    qDebug() << "sslLibraryVersionNumber:" << QSslSocket::sslLibraryVersionNumber();
    qDebug() << "sslLibraryVersionString:" << QSslSocket::sslLibraryVersionString();
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // Logging configuration has to happen AFTER initialization of QApplication.
    // Because Qt wants to mess around with the console stuff on Windows
    // platforms.
    configureLogging();
    dumpSslInformation();

    auto& s = QString::fromStdString;

    app.setOrganizationName(s(application_metadata::ORGANIZATION_NAME));
    app.setApplicationName(s(application_metadata::APPLICATION_NAME));

    // Initialize dependency graph for app.
    // This stuff is all stack-allocated: it's not dangerous, because this is
    // the highest level of stack.  It will be in scope for the entire lifetime
    // of the program.

    // Token store is spooky action at a distance that's used to thread the
    // token through the various dependencies.
    TokenStoreImpl tokenStore;

    QtHttpGetter httpGetter(&tokenStore);
    QtHttpPoster httpPoster(&tokenStore);
    QtHttpPutter httpPutter(&tokenStore);
    QtSizeGetter sizeGetter;

    GroupMapperImpl groupMapper(&httpGetter);
    CategoryMapper categoryMapper(&httpGetter);

    LookupRegistryImpl lookupRegistry(&categoryMapper, &groupMapper);
    ConverterRegistry converterRegistry;
    ConverterRegistry::initializeStandardConverters(
        converterRegistry, &lookupRegistry
    );
    MappingEngineImpl mappingEngine(&converterRegistry);


    ArticleTypeMapper typeMapper;
    HttpFigshareGateway gateway(
        &httpGetter, &httpPoster, &httpPutter, categoryMapper, &groupMapper
    );

    PartPreparerImpl partPreparer;
    FileSpecGeneratorImpl fileSpecGenerator(&sizeGetter);

    DriverImpl driver(
        &gateway,
        &partPreparer,
        &fileSpecGenerator,
        &mappingEngine
    );

    // Model owns the various user-manipulable data.
    // Pass the converter registry by implicit const reference.
    ModelImpl model(converterRegistry);

    Presenter* presenter = new PresenterImpl(&model, &driver, &tokenStore);
    ViewImpl* view = new ViewImpl(presenter);

    // To break the cyclic dependency we have to setView on the presenter after
    // it's been constructed.
    presenter->setView(view);
    presenter->initializeView();

    view->show();

    return app.exec();
}

