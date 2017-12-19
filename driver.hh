#ifndef DRIVER_HH
#define DRIVER_HH

#include "article_mapper.hh"
#include "file_info.hh"
#include "file_part.hh"
#include "figshare_gateway.hh"
#include "part_preparer.hh"
#include "excel_row.hh"
#include "file_spec_generator.hh"
#include "progress_reporter.hh"

class Driver {
public:
    Driver(
        FigshareGateway* gateway,
        PartPreparer* partPreparer,
        FileSpecGenerator* fileSpecGenerator,
        ArticleMapper* articleMapper
    ) : gateway(gateway),
        partPreparer(partPreparer), 
        fileSpecGenerator(fileSpecGenerator),
        articleMapper(articleMapper) {
        progressReporter = NULL;
    }

    void handleRow(const ExcelRow row) const;
    void handleUpload(const string stemArticle, const UploadCreationRequest ucr) const;
    void handlePart(const FileInfo sourceFile, const FilePart partSpec) const;
    void setProgressReporter(ProgressReporter* reporter);
    void log(string message) const;

private:
    FileSpecGenerator* fileSpecGenerator;
    FigshareGateway* gateway;
    PartPreparer* partPreparer;
    ArticleMapper* articleMapper;
    ProgressReporter* progressReporter;
};

#endif // DRIVER_HH
