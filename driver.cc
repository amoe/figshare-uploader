#include <iostream>
#include <vector>
#include <QDebug>
#include <QApplication>
#include "xlsx.hh"
#include "article_mapper.hh"
#include "http_poster.hh"
#include "figshare_gateway.hh"
#include "requests.hh"
#include "http_getter.hh"
#include "category_mapper.hh"

using std::string;
using std::vector;
using std::cout;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    HttpGetter* getter = new QtHttpGetter;

    string result = getter->request("https://api.figshare.com/v2/categories");
    
    CategoryMapper mapper(result);

    return 0;
}

void foo() {
    // qDebug() << "starting";

    // string inputPath("resources/test.xlsx");

    // XlsxReader theReader(inputPath);
    // ArticleTypeMapper typeMapper;
    // ArticleMapper mapper(typeMapper);
    // HttpPoster* poster = new QtHttpPoster;
    // FigshareGateway* gateway = new HttpFigshareGateway(poster);

    // for (int i = 2; i <= 6; i++) {
    //     vector<string> row = theReader.rowToString(i);
    //     ArticleCreationRequest request = mapper.mapFromExcel(row);
        
    //     string uploadJson = mapper.mapToFigshare(request);
        
    //     std::cout << uploadJson << std::endl;
    // }
}
