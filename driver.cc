#include <iostream>
#include <vector>
#include <QDebug>
#include "xlsx.hh"
#include "article_mapper.hh"
#include "http_poster.hh"
#include "figshare_gateway.hh"
#include "requests.hh"

using std::string;
using std::vector;

int main(int argc, char **argv) {
    qDebug() << "starting";

    string inputPath("resources/test.xlsx");

    XlsxReader theReader(inputPath);
    ArticleTypeMapper typeMapper;
    ArticleMapper mapper(typeMapper);
    HttpPoster* poster = new QtHttpPoster;
    FigshareGateway* gateway = new HttpFigshareGateway(poster);

    for (int i = 2; i <= 6; i++) {
        vector<string> row = theReader.rowToString(i);
        ArticleCreationRequest request = mapper.mapFromExcel(row);
        
        string uploadJson = mapper.mapToFigshare(request);
        
        std::cout << uploadJson << std::endl;
    }

    return 0;
}
