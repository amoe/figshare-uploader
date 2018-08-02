#ifndef OBJECT_MOTHER_HH
#define OBJECT_MOTHER_HH

#include "file_info.hh"
#include "upload_container_info.hh"
#include "requests.hh"
#include "responses.hh"
#include "upload_command.hh"
#include "article_mapper.hh"
#include "raw_literals.hh"

class ObjectMother {
public:
    static ArticleGetResponse makeArticleGetResponse();
    static ArticleCreationRequest makeArticleCreationRequest();
    static ArticleCreationResponse makeArticleCreationResponse();
    static FileInfo makeFileInfo();
    static UploadContainerInfo makeUploadContainerInfo(int nParts);
    static FilePart makeFilePart(int i);
    static UploadCreationRequest makeUploadCreationRequest();
    static UploadCreationResponse makeUploadCreationResponse();
    static UploadCommand makeUploadCommand();
};

#endif // OBJECT_MOTHER_HH
