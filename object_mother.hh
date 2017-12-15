#ifndef OBJECT_MOTHER_HH
#define OBJECT_MOTHER_HH

#include "file_info.hh"
#include "upload_container_info.hh"

class ObjectMother {
public:
    static FileInfo makeFileInfo();
    static UploadContainerInfo makeUploadContainerInfo(int nParts);
    static FilePart makeFilePart(int i);
};

#endif // OBJECT_MOTHER_HH
