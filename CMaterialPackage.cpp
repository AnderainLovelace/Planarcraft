#include "KuroConfig.h"
#include "sdl/sdlimg.h"
#include "CMaterialPackage.h"
#include "CError.h"

#define LOCAL_PATH      "../material/"
#define PACKAGE_NAME    "package.tar"

namespace kuro {
    CMaterialPackage::CMaterialPackage(Method method)  {
        initialize(method);
    }
    CMaterialPackage::CMaterialPackage()  {
    }

    void CMaterialPackage::initialize(Method method) {
        if (method == Method::Package) {
            _useLocal = false;
            _path = PACKAGE_NAME;
            _tarReader.open(_path);
            if (!_tarReader.opened())
                throw CException(CString("can no open package '") + _path + "'");
        }
        else if (method == Method::Local) {
            _useLocal = true;
            _path = LOCAL_PATH;
        }
    }

    SDL_Surface * CMaterialPackage::loadImage(const CString & fileName) {
        return _useLocal ? loadLocalImage(fileName) : loadPackageImage(fileName);
    }
    SDL_Surface * CMaterialPackage::loadLocalImage(const CString & fileName) {
        SDL_Surface *   surface = nullptr;
        SDL_Surface *   optSurface = nullptr;
        bool alpha = false;

#ifndef __NDLESS__
        surface = IMG_Load(_path + fileName);

        if (surface == nullptr) {
            throw CException(CString("can not open local file '") + fileName + "'");
        }
        optSurface = SDL_DisplayFormatAlpha(surface);
        SDL_FreeSurface(surface);

        return optSurface;
#else
        return nullptr;
#endif
    }
    SDL_Surface * CMaterialPackage::loadPackageImage(const CString & fileName) {
        if (!_tarReader.opened())
            throw CException("MaterialPackage : package not opened");

        SDL_Surface *   surface = nullptr;
        SDL_Surface *   optSurface = nullptr;
        SDL_RWops *     rw;
        bool            alpha = false;

        void *          data = nullptr;
        int             fileSize;
        kuro::CTarReader::ReadResult result;

        data = _tarReader.getFileContent(fileName, &fileSize, &result);
        
        if (data == nullptr)
            throw CException(CString("can no open file in package '") + fileName + "'");

        rw = SDL_RWFromMem(data, fileSize);

        if (SDLIMG_isPNG(rw)) {
            surface = SDLIMG_LoadPNG_RW(rw);
            SDL_FreeRW(rw);
            alpha = true;
        }
        else if (SDLIMG_isJPG(rw)) {
            surface = SDLIMG_LoadJPG_RW(rw);
            SDL_FreeRW(rw);
        }
        else {
            surface = SDL_LoadBMP_RW(rw, true);
        }

        delete[] data;

        if (alpha)
            optSurface = SDL_DisplayFormatAlpha(surface);
        else
            optSurface = SDL_DisplayFormat(surface);
        SDL_FreeSurface(surface);

        return optSurface;
    }
}