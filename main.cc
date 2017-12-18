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

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // Construct the top-level object graph on the stack
    char* token_ = getenv("TOKEN");
    if (token_ == NULL) {
        throw std::runtime_error("token must exist in environment");
    }
    std::string token(token_);

    QtHttpGetter httpGetter(token);
    QtHttpPoster httpPoster(token);
    QtHttpPutter httpPutter(token);
    QtSizeGetter sizeGetter;

    debugf("loading categories");
    string result = httpGetter.request("https://api.figshare.com/v2/categories");
    CategoryMapper categoryMapper(result);
    debugf("loaded categories");

    ArticleTypeMapper typeMapper;
    HttpFigshareGateway gateway(&httpGetter, &httpPoster, &httpPutter, categoryMapper);
    PartPreparerImpl partPreparer;
    FileSpecGeneratorImpl fileSpecGenerator(&sizeGetter);
    ArticleMapperImpl articleMapper(typeMapper, categoryMapper);

    Driver driver(&gateway, &partPreparer, &fileSpecGenerator, &articleMapper);

    Presenter* presenter = new PresenterImpl(&driver);
    ViewImpl* view = new ViewImpl(presenter);

    // To break the cyclic dependency we have to setView on the presenter after
    // it's been constructed.
    presenter->setView(view);
    view->show();

    return app.exec();
}
