#ifndef _KURO_CSTRING_H_
#define _KURO_CSTRING_H_

namespace kuro {
    class CString {
    public:
        CString(const char *);
        CString(const CString &);
        CString();
        ~CString();

        CString & operator=(const CString &);
        CString & operator=(const char *);

        bool operator==(const CString &);
        bool operator==(const char *);
        bool operator==(const char);

        CString operator+(const CString &);
        CString operator+(const char *);

        CString & operator+=(const CString &);
        CString & operator+=(const char *);

        const char * cstr() const;
        int size() const;

        operator const char * () const;

    private:
        CString(char *, bool move);
        char * _string;
    };
}

#endif