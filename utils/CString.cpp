#include "CString.h"
#include "string.h"
#include "stdio.h"
namespace kuro {
    CString::CString(const char * s) {
        _string = new char[strlen(s) + 1];
        strcpy(_string, s);
    }
    CString::CString(const CString & s) {
        _string = new char[strlen(s._string) + 1];
        strcpy(_string, s._string);
    }
    CString::CString() {
        _string = new char[1];
        *_string = '\0';
    }
    CString::~CString() {
        delete[] _string;
    }

    CString & CString::operator=(const CString & rsh) {
        return this->operator=(rsh._string);
    }
    CString & CString::operator=(const char * rsh) {
        if (rsh == _string)
            return *this;

        delete[] _string;
        _string = new char[strlen(rsh) + 1];
        strcpy(_string, rsh);

        return *this;
    }

    CString CString::operator+(const CString & rsh) {
        return (CString(_string) += rsh);
    }
    CString CString::operator+(const char * rsh) {
        return (CString(_string) += rsh);
    }

    CString & CString::operator+=(const CString & rsh) {
        return this->operator+=(rsh._string);
    }

    CString & CString::operator+=(const char * rsh) {
        int len1 = strlen(_string), len2 = strlen(rsh);
        char * pre_string = _string;
        _string = new char[len1 + len2 + 1];
        strcpy(_string, pre_string);
        strcat(_string, rsh);
        delete[] pre_string;
        
        return *this;
    }

    int CString::size() const {
        return strlen(_string);
    }

    CString::operator const char * () const {
        return _string;
    }

    const char * CString::cstr() const {
        return _string;
    }

    bool CString::operator==(const CString & s) {
        return strcmp(s._string, _string) == 0;
    }
    bool CString::operator==(const char * str) {
        return strcmp(str, _string) == 0;
    }
    bool CString::operator==(const char c) {
        return (bool)(size() == 1 && _string[0] == c);
    }
}