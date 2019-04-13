#include <iostream>
#include <vector>
#include <stdexcept>
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
#include "http_putter.hh"
#include "category_mapper.hh"
#include "size_getter.hh"
#include "file_spec_generator.hh"
#include "io_slicer.hh"
#include "part_preparer.hh"
#include <QDataStream>

using std::string;
using std::vector;
using std::cout;

void spew(string filename, vector<char> data) {
    QString path = QString::fromStdString(filename);
    QFile foo(path);
    foo.open(QIODevice::WriteOnly);
    QDataStream bar(&foo);
    
    for (int i = 0; i < data.size(); i++) {
        bar.writeRawData(&(data.at(i)), 1);
    }
}

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
    HttpPutter* putter = new QtHttpPutter(token);

    string result = getter->request("https://api.figshare.com/v2/categories");
    CategoryMapper categoryMapper(result);
    XlsxReader theReader(inputPath);
    ArticleTypeMapper typeMapper;
    ArticleMapper mapper(typeMapper, categoryMapper);
    HttpPoster* poster = new QtHttpPoster(token);
    FigshareGateway* gateway = new HttpFigshareGateway(
        getter, poster, putter, categoryMapper
    );

    SizeGetter* sg = new QtSizeGetter();
    FileSpecGenerator* fsg = new FileSpecGeneratorImpl(sg);

    for (int i = 2; i <= 6; i++) {
        vector<string> row = theReader.rowToString(i);
        ArticleCreationRequest request = mapper.mapFromExcel(row);
        string uploadJson = mapper.mapToFigshare(request);

        std::cout << uploadJson << std::endl;

        auto articleCreateResponse = gateway->createArticle(request);

        // TODO: GET the thing here and pull out the id.

        string stemArticle = articleCreateResponse.location;

        std::cout << stemArticle << std::endl;

        // Now we get the info on the newly-created article.

        ArticleGetResponse articleData = gateway->getArticle(stemArticle);

        int articleId = articleData.id;

        string relationField = row.at(15);

        IOSlicer* slicer = new FileSlicer(relationField);
        PartPreparer pp(slicer);

        std::cout << relationField << std::endl;

        UploadCreationRequest ucr = fsg->getFileSpec(relationField);

        std::cout << ucr.size << std::endl;
        std::cout << ucr.md5 << std::endl;
        std::cout << ucr.name << std::endl;

        UploadCreationResponse response = gateway->createUpload(stemArticle, ucr);


        std::cout << "upload container url: " << response.location << std::endl;



        // GETTING FILE INFO

        FileInfo info = gateway->getUploadInfo(response.location);

        std::cout << info.uploadContainerUrl << std::endl;
        
        int uploadId = info.id;
        std::cout << "id from info is " << info.id << std::endl;
        
        UploadContainerInfo uci = gateway->getUploadContainerInfo(
            info.uploadContainerUrl
        );

        std::cout << "token is " << uci.token << std::endl;
        std::cout << "size is " << uci.size << std::endl;


        for (int j = 0; j < uci.parts.size(); j++) {
            
            UploadCommand uc = pp.prepareUpload(info, uci.parts.at(j));
            std::cout  << "would put to " << uc.getUrl() << std::endl;
            std::cout  << "chunk size is " << uc.getData().size() << std::endl;


            string filename = std::to_string(j + 1) + ".dat";

            spew(filename, uc.getData());

            PartPutResponse ppr = gateway->putUpload(uc);
            std::cout << "UPLOAD WAS PUT" << std::endl;

            // The missing piece is a call to completeUpload() on the gateway.
            // That basically does this.  "id" which is available from somewhere
            // then you post to the ID again?  confusing

        }

        std::cout << "Completing request: articleId=" << articleId
                  << ", uploadId=" << uploadId << std::endl;
        string result = gateway->completeUpload(articleId, uploadId);
        std::cout << result << std::endl;
            
        return 0;
    }

    return 0;
}

