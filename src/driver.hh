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
    virtual void handleRow(const ExcelRow row, const string inputPath,
                   const MappingScheme& mappingScheme) const = 0;
    virtual void handleUpload(
        const string stemArticle,
        const string sourcePath,    // the ABSOLUTE path that can be opened
        const UploadCreationRequest ucr
    ) const = 0;
    virtual void handlePart(
        const string sourcePath,
        const FileInfo sourceFile, 
        const FilePart partSpec
    ) const = 0;
    virtual void setProgressReporter(ProgressReporter* reporter) = 0;
    virtual void log(string message) const = 0;
};

class DriverImpl: public Driver {
public:
    DriverImpl(
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
    ) const override;
    void handleUpload(
        const string stemArticle,
        const string sourcePath,
        const UploadCreationRequest ucr
    ) const override;
    void handlePart(
        const string sourcePath,
        const FileInfo sourceFile, 
        const FilePart partSpec
    ) const override;
    void setProgressReporter(ProgressReporter* reporter) override;
    void log(string message) const override;

private:
    FigshareGateway* gateway;
    PartPreparer* partPreparer;
    FileSpecGenerator* fileSpecGenerator;
    ArticleMapper* articleMapper;
    ProgressReporter* progressReporter;
    MappingEngine* mappingEngine;
};

#endif // DRIVER_HH
