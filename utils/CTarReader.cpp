#include "CTarReader.h"
#include "string.h"
#include "ctype.h"
#define BLOCK_SIZE 512

typedef unsigned char byte;

namespace kuro {
    /* 八进制字符串转整数 */
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
    /* 获取文件头长度 */
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
            /*无法打开 */
            if (result != nullptr)
                *result = ReadResult::CanNotOpenTar;
            return nullptr;
        }
        /* 开始搜索文件 */
        while (!feof(_file)) {
            int     bytesToRead;
            /* 读取头部 */
            fread(&header, sizeof(header), 1, _file);
            /* 空的文件名（尾部空block）读取结束 */
            if (strcmp(header.fileName, "") == 0) {
                break;
            }
            bytesToRead = getHeaderSize(&header);
            /* 跳过文件夹 */
            if (bytesToRead == 0) {
                continue;
            }
            /* 找到指定文件 */
            if (strcmp(fileName, header.fileName) == 0) {
                // 比文件长度多申请一个字节，用于直接生成字符串
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
            /* 非指定文件，跳过 */
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