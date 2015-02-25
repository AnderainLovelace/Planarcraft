#ifndef _CTARREADER_H_
#define _CTARREADER_H_

#include "stdio.h"
#include "kuro/utils/CString.h"

namespace kuro {
    class CTarReader {
    public:
        CTarReader();
        CTarReader(const CString & fileName);
        ~CTarReader();

        bool open(const CString & fileName);
        void close();
        bool opened() { return _opened; }

        enum class ReadResult {
            CanNotOpenTar, Success, FileNotFound
        };

        void * getFileContent(const CString & fileName, 
            int * pSize = nullptr, ReadResult * result = nullptr);
        CString getFileAsString(const CString & fileName);

    protected:
        typedef struct tag_TAR_HEADER {
            char fileName[100];
            char mode[8];
            char uid[8];
            char gid[8];
            char fileSize[12];
            char lastModification[12];
            char checksum[8];
            char typeFlag;
            char linkedFileName[100];
            char ustarIndicator[6];
            char ustarVersion[2];
            char ownerUserName[32];
            char ownerGroupName[32];
            char deviceMajorNumber[8];
            char deviceMinorNumber[8];
            char filenamePrefix[155];
            char padding[12];
        }
        TAR_HEADER;

        bool _opened;
        FILE * _file;

        int getHeaderSize(const TAR_HEADER * header);
        int octStringToInteger(const char * str);
    };
}

#endif