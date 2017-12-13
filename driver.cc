#include <iostream>
#include <vector>
#include <cstdlib>
#include <QDebug>
#include <QApplication>
#include "xlsx.hh"
#include "article_mapper.hh"
#include "upload_container_info.hh"
#include "file_info.hh"
#include "http_poster.hh"
#include "figshare_gateway.hh"
#include "requests.hh"
#include "http_getter.hh"
#include "category_mapper.hh"
#include "size_getter.hh"
#include "file_spec_generator.hh"
#include "io_slicer.hh"
#include "part_preparer.hh"

using std::string;
using std::vector;
using std::cout;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    qDebug() << "starting";

    char* token_ = getenv("TOKEN");
    
    if (token_ == NULL) {
        throw std::runtime_error("token must exist in environment");
    }

    std::string token(token_);

    string inputPath("resources/test.xlsx");


    HttpGetter* getter = new QtHttpGetter(token);
    string result = getter->request("https://api.figshare.com/v2/categories");
    CategoryMapper categoryMapper(result);
    XlsxReader theReader(inputPath);
    ArticleTypeMapper typeMapper;
    ArticleMapper mapper(typeMapper, categoryMapper);
    HttpPoster* poster = new QtHttpPoster(token);
    FigshareGateway* gateway = new HttpFigshareGateway(
        getter, poster, categoryMapper
    );

    SizeGetter* sg = new QtSizeGetter();
    FileSpecGenerator* fsg = new FileSpecGeneratorImpl(sg);



    string stemArticle = "https://api.figshare.com/v2/account/articles/5697091";

    for (int i = 2; i <= 6; i++) {
        vector<string> row = theReader.rowToString(i);
        // ArticleCreationRequest request = mapper.mapFromExcel(row);
        // string uploadJson = mapper.mapToFigshare(request);

        // std::cout << uploadJson << std::endl;

        // auto response = gateway->createArticle(request);

        // std::cout << response.location << std::endl;

        string relationField = row.at(15);

        IOSlicer* slicer = new FileSlicer(relationField);
        PartPreparer pp(slicer);

        std::cout << relationField << std::endl;

        UploadCreationRequest ucr = fsg->getFileSpec(relationField);

        std::cout << ucr.size << std::endl;
        std::cout << ucr.md5 << std::endl;
        std::cout << ucr.name << std::endl;

        auto response = gateway->createUpload(stemArticle, ucr);

        std::cout << response.location << std::endl;


        FileInfo info = gateway->getUploadInfo(response.location);

        std::cout << info.uploadContainerUrl << std::endl;
        
        UploadContainerInfo uci = gateway->getUploadContainerInfo(
            info.uploadContainerUrl
        );

        std::cout << "token is " << uci.token << std::endl;
        std::cout << "size is " << uci.size << std::endl;


        for (int j = 0; j < uci.parts.size(); j++) {
            UploadCommand uc = pp.prepareUpload(info, uci.parts.at(j));
            std::cout  << "would put to " << uc.getUrl() << std::endl;
        }


        return 0;
    }

    return 0;
}

