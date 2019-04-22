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
#include "mapping_types.hh"
#include "mapping_engine.hh"

class Driver {
public:
    Driver(
        FigshareGateway* gateway,
        PartPreparer* partPreparer,
        FileSpecGenerator* fileSpecGenerator,
        ArticleMapper* articleMapper,
        MappingEngine* mappingEngine
    ) : gateway(gateway),
        partPreparer(partPreparer), 
        fileSpecGenerator(fileSpecGenerator),
        articleMapper(articleMapper),
        mappingEngine(mappingEngine) {
        progressReporter = NULL;
    }

    void handleRow(
        const ExcelRow row, const string inputPath,
        const MappingScheme& mappingScheme
    ) const;
    void handleUpload(
        const string stemArticle,
        const string sourcePath,    // the ABSOLUTE path that can be opened
        const UploadCreationRequest ucr
    ) const;
    void handlePart(
        const string sourcePath,
        const FileInfo sourceFile, 
        const FilePart partSpec
    ) const;
    void setProgressReporter(ProgressReporter* reporter);
    void log(string message) const;

private:
    FigshareGateway* gateway;
    PartPreparer* partPreparer;
    FileSpecGenerator* fileSpecGenerator;
    ArticleMapper* articleMapper;
    ProgressReporter* progressReporter;
    MappingEngine* mappingEngine;
};

#endif // DRIVER_HH
