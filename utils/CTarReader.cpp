#include "CTarReader.h"
#include "string.h"
#include "ctype.h"
#define BLOCK_SIZE 512

typedef unsigned char byte;

namespace kuro {
    /* �˽����ַ���ת���� */
    int CTarReader::octStringToInteger(const char * str) {
        size_t t = 0, mul = 0;
        const char * p = strchr(str, '\0') - 1;
        while (p >= str) {
            t += (*p - '0') << mul;
            mul += 3; // *=8
            p--;
        }
        return t;
    }
    /* ��ȡ�ļ�ͷ���� */
    int CTarReader::getHeaderSize(const TAR_HEADER * header) {
        char szNum[12], *ptr = szNum;
        strncpy(szNum, header->fileSize, 12);
        szNum[11] = '\0';
        while (!isdigit(*ptr)) {
            ++ptr;
        }
        return octStringToInteger(ptr);
    }

    CTarReader::CTarReader() : _file(nullptr), _opened(false) {
    }
    CTarReader::CTarReader(const CString & fileName) {
        open(fileName);
    }
    CTarReader::~CTarReader() {
        close();
    }

    bool CTarReader::open(const CString & fileName) {
        _file = fopen(fileName, "rb");
        _opened = _file != nullptr;
        return _opened;
    }
    void CTarReader::close() {
        if (_opened) {
            fclose(_file);
            _opened = false;
        }
    }
    void * CTarReader::getFileContent(const CString & fileName, int * pSize, ReadResult * result) {
        TAR_HEADER  header;
        fseek(_file, 0, SEEK_SET);
        if (_file == nullptr) {
            /*�޷��� */
            if (result != nullptr)
                *result = ReadResult::CanNotOpenTar;
            return nullptr;
        }
        /* ��ʼ�����ļ� */
        while (!feof(_file)) {
            int     bytesToRead;
            /* ��ȡͷ�� */
            fread(&header, sizeof(header), 1, _file);
            /* �յ��ļ�����β����block����ȡ���� */
            if (strcmp(header.fileName, "") == 0) {
                break;
            }
            bytesToRead = getHeaderSize(&header);
            /* �����ļ��� */
            if (bytesToRead == 0) {
                continue;
            }
            /* �ҵ�ָ���ļ� */
            if (strcmp(fileName, header.fileName) == 0) {
                // ���ļ����ȶ�����һ���ֽڣ�����ֱ�������ַ���
                byte *  data = new byte[bytesToRead + 1];
                byte *  pdata = data;
                if (pSize != nullptr) {
                    *pSize = bytesToRead;
                }
                while (!feof(_file) && bytesToRead > 0) {
                    byte    buffer[BLOCK_SIZE];
                    size_t  thisBlockRead = bytesToRead > BLOCK_SIZE ? BLOCK_SIZE : bytesToRead;
                    fread(buffer, BLOCK_SIZE, sizeof(byte), _file);
                    memcpy(pdata, buffer, thisBlockRead);
                    pdata += thisBlockRead;
                    bytesToRead -= BLOCK_SIZE;
                }
                if (result != nullptr)
                    *result = ReadResult::Success;
                return data;
            }
            /* ��ָ���ļ������� */
            else {
                int totalSize;
                if (bytesToRead % BLOCK_SIZE == 0) {
                    totalSize = bytesToRead;
                }
                else {
                    totalSize = (bytesToRead / BLOCK_SIZE + 1) * BLOCK_SIZE;
                }
                fseek(_file, totalSize, SEEK_CUR);
            }
        }
        if (result != nullptr)
            *result = ReadResult::FileNotFound;
        return nullptr;
    }

    CString CTarReader::getFileAsString(const CString & fileName) {
        int fileSize;
        char * data = (char *)getFileContent(fileName, &fileSize);
        if (data == nullptr)
            return "";
        data[fileSize] = '\0';
        CString strTemp(data);
        delete[] data;
        return strTemp;
    }
}