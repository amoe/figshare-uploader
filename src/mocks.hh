#include <QJsonObject>
#include <QJsonValue>
#include <gmock/gmock.h>
#include "file_info.hh"
#include "mapping_types.hh"
#include "requests.hh"
#include "responses.hh"
#include "article_mapper.hh"
#include "converter_registry.hh"
#include "part_preparer.hh"
#include "interfaces.hh"
#include "file_spec_generator.hh"
#include "upload_container_info.hh"
#include "figshare_gateway.hh"
#include "excel_row.hh"
#include "driver.hh"

class MockPartPreparer : public PartPreparer {
public:
    MOCK_METHOD3(
        prepareUpload,
        UploadCommand(const string sourcePath, const FileInfo info, const FilePart part)
    );
};


class MockModel: public Model {
public:
    MOCK_METHOD1(setSourceFile, void(string));
    MOCK_METHOD0(getAvailableEncoders, vector<FieldEncoder>&());
    MOCK_METHOD2(bindRow, void(int, int));
    MOCK_METHOD1(setHeaderFields, void(vector<string>));
    MOCK_METHOD1(addFieldEncoder, void(FieldEncoder));
    MOCK_METHOD2(replaceFieldEncoder, void(int, FieldEncoder));
    MOCK_METHOD1(replaceFieldMappings, void(MappingScheme));

    MOCK_CONST_METHOD0(getFieldMappings, const MappingScheme&());
    MOCK_CONST_METHOD0(getSourceFile, const optional<string>());
    MOCK_CONST_METHOD0(getHeaderFields, const vector<string>());
    MOCK_CONST_METHOD0(getConverterRegistry, const ConverterRegistry&());
    MOCK_CONST_METHOD0(dumpMappingScheme, void());
};

class MockView: public View {
public:
    MOCK_METHOD0(getSelectedFile, string());
    MOCK_METHOD0(getToken, string());
    MOCK_METHOD1(reportError, void(string));
    MOCK_METHOD1(addLog, void(string));
    MOCK_METHOD0(showFileDialog, bool());
    MOCK_METHOD1(setProgressReporter, void(ViewProgressAdapter*));
    MOCK_METHOD0(showAboutDialog, void());
    MOCK_METHOD3(
        showSettingsDialog,
        void(
            vector<string>,
            const MappingScheme&,
            const ConverterRegistry&
        )
    );

    MOCK_METHOD1(setSourceFile, void(string));
    MOCK_METHOD1(setToken, void(string));
    MOCK_METHOD1(setAvailableEncoders, void(vector<FieldEncoder>&));
    MOCK_METHOD1(infoBox, void(string));
    MOCK_METHOD0(forceRefreshFieldMappings, void());
};


class MockFigshareGateway: public FigshareGateway {
public:
    MOCK_METHOD1(createArticle, ArticleCreationResponse(ArticleCreationRequest));
    MOCK_METHOD1(createArticle, ArticleCreationResponse(QJsonObject));
    MOCK_METHOD2(createUpload, UploadCreationResponse(string, UploadCreationRequest));
    MOCK_METHOD1(getUploadInfo, FileInfo(string));
    MOCK_METHOD1(getUploadContainerInfo, UploadContainerInfo(string));
    MOCK_METHOD1(putUpload, PartPutResponse(UploadCommand));
    MOCK_METHOD1(completeUpload, string(string));
    MOCK_METHOD1(getArticle, ArticleGetResponse(string));
};

class MockFileSpecGenerator : public FileSpecGenerator {
public:
    MOCK_METHOD1(getFileSpec, UploadCreationRequest(string path));
};

class MockLookupRegistry: public LookupRegistry {
public:
    MOCK_METHOD2(lookupByString, QJsonValue(LookupType, string));
};

class MockHttpGetter : public HttpGetter {
public:
    MOCK_METHOD1(request, string(string url));
};

class MockArticleMapper : public ArticleMapper {
public:
    MOCK_METHOD1(mapFromExcel, ArticleCreationRequest(const vector<string> excelRow));
    MOCK_METHOD1(mapToFigshare, string(ArticleCreationRequest request));
};



class MockDriver: public Driver {
public:
    MOCK_CONST_METHOD3(handleRow, void(ExcelRow, string, const MappingScheme&));
    MOCK_CONST_METHOD3(handleUpload, void(string, string, UploadCreationRequest));
    MOCK_CONST_METHOD3(handlePart, void(string, FileInfo, FilePart));
    MOCK_CONST_METHOD1(log, void(string));
    MOCK_METHOD1(setProgressReporter, void(ProgressReporter*));
};

class MockTokenStore: public TokenStore {
public:
    MOCK_CONST_METHOD0(getToken, string());
    MOCK_METHOD1(setToken, void(string));
};


class MockMappingEngine: public MappingEngine {
public:
    MOCK_CONST_METHOD2(convert, MappingOutput(vector<string>, MappingScheme));
};
