#ifndef OBJECT_MOTHER_HH
#define OBJECT_MOTHER_HH

#include "file_info.hh"
#include "upload_container_info.hh"
#include "requests.hh"
#include "responses.hh"

class ObjectMother {
public:
    static ArticleGetResponse makeArticleGetResponse();
    static ArticleCreationRequest makeArticleCreationRequest();
    static ArticleCreationResponse makeArticleCreationResponse();
    static FileInfo makeFileInfo();
    static UploadContainerInfo makeUploadContainerInfo(int nParts);
    static FilePart makeFilePart(int i);
    static UploadCreationRequest makeUploadCreationRequest();
};

#endif // OBJECT_MOTHER_HH
