#include <iostream>
#include <QApplication>
#include <QThread>
#include "driver.hh"
#include "figshare_gateway.hh"
#include "part_preparer.hh"
#include "file_spec_generator.hh"
#include "article_mapper.hh"
#include "view.hh"


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
    FileSlicer ioSlicer = FileSlicer("/etc/passwd"); // this is a big problem

    string result = httpGetter.request("https://api.figshare.com/v2/categories");
    CategoryMapper categoryMapper(result);

    ArticleTypeMapper typeMapper;
    HttpFigshareGateway gateway(&httpGetter, &httpPoster, &httpPutter, categoryMapper);
    PartPreparerImpl partPreparer(&ioSlicer);
    FileSpecGeneratorImpl fileSpecGenerator(&sizeGetter);
    ArticleMapperImpl articleMapper(typeMapper, categoryMapper);

    ViewImpl* view = new ViewImpl;
    
    view->show();

    return app.exec();
}
