#ifndef _CERROR_H_
#define _CERROR_H_

#include "utils/CString.h"

namespace kuro {
    class CException {
    public:
        CException(const CString & message) : _message(message) {}
        CString & getMessage() { return _message; }
    protected:
        CString _message;
    };
}

#endif