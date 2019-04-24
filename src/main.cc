#include <iostream>
#include <QApplication>
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

int main(int argc, char **argv) {
    QApplication app(argc, argv);

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
    MappingEngine mappingEngine(&converterRegistry);


    ArticleTypeMapper typeMapper;
    HttpFigshareGateway gateway(
        &httpGetter, &httpPoster, &httpPutter, categoryMapper, &groupMapper
    );

    PartPreparerImpl partPreparer;
    FileSpecGeneratorImpl fileSpecGenerator(&sizeGetter);
    CustomFieldMapper customFieldMapper;
    ArticleMapperImpl articleMapper(typeMapper, categoryMapper, customFieldMapper, &groupMapper);

    DriverImpl driver(
        &gateway,
        &partPreparer,
        &fileSpecGenerator,
        &articleMapper,
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

