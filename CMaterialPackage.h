#ifndef _CMATERIALPACKAGE_H_
#define _CMATERIALPACKAGE_H_

#include "utils/CTarReader.h"
#include "utils/CString.h"
#include SDL_H_HEADER_FILE

namespace kuro {
    class CMaterialPackage {
    public:
        enum class Method {
            Package, Local
        };

        CMaterialPackage();
        CMaterialPackage(Method method);

        void initialize(Method method);

        SDL_Surface * loadImage(const CString & fileName);

    protected:
        CTarReader _tarReader;
        bool _useLocal;
        CString _path;

        SDL_Surface * loadLocalImage(const CString & fileName);
        SDL_Surface * loadPackageImage(const CString & fileName);
    };
}

#endif