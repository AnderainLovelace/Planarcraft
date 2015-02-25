#include "CSurface.h"
#include "kuro/CApplication.h"
#include "kuro/sdl/rotozoom.h"

namespace kuro {
    CSurface::CSurface(int w, int h, Uint32 color) {
        _surface = createSurface(w, h);
        fill(color);
    }

    CSurface::CSurface(const CString & fileName) {
        _surface = CApplication::getInstance()->getPackage().loadImage(fileName);
    }

    CSurface::CSurface() : _surface(nullptr) {
    }
    
    CSurface::CSurface(SDL_Surface * surface) : _surface(surface) {
    }

    CSurface::~CSurface() {
        if (_surface != nullptr)
            SDL_FreeSurface(_surface);
    }

    CVec2 CSurface::getSize() {
        return CVec2(_surface->w, _surface->h);
    }

    void CSurface::fill(Uint32 color) {
        SDL_FillRect(_surface, nullptr, color);
    }

    void CSurface::setPixel(int x, int y, Uint32 pixel) {
        int     bpp;
        Uint8 * p;

        if (x < 0 || x >= _surface->w || y < 0 || y >= _surface->h)
            return;

        bpp = _surface->format->BytesPerPixel;
        p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;

        switch (bpp) {
        case 1:
            *p = (Uint8)pixel;
            break;

        case 2:
            *(Uint16 *)p = (Uint16)pixel;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (Uint8)((pixel >> 16) & 0xff);
                p[1] = (Uint8)((pixel >> 8) & 0xff);
                p[2] = (Uint8)(pixel & 0xff);
            }
            else {
                p[0] = (Uint8)(pixel & 0xff);
                p[1] = (Uint8)((pixel >> 8) & 0xff);
                p[2] = (Uint8)((pixel >> 16) & 0xff);
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
        }
    }

    void CSurface::applyTo(CSurface & destination, int x, int y, CRect * clipRect) {
        auto destSurface = destination.getSDLSurface();
        SDL_Rect offset; offset.x = x; offset.y = y;
        if (clipRect != nullptr) {
            SDL_Rect srcRect = { clipRect->x, clipRect->y, clipRect->w, clipRect->h };
            SDL_BlitSurface(_surface, &srcRect, destSurface, &offset);
        }
        else {
            SDL_BlitSurface(_surface, nullptr, destSurface, &offset);
        }
    }

    CSurface * CSurface::rotozoom(double xZoom, double yZoom, double angle, bool smooth) {
        SDL_Surface * zoomedSurface = rotozoomSurfaceXY(_surface, angle, xZoom, yZoom, smooth);
        return new CSurface(zoomedSurface);
    }

    CSurface * CSurface::zoom(double xZoom, double yZoom, bool smooth) {
        SDL_Surface * zoomedSurface = zoomSurface(_surface, xZoom, yZoom, smooth);
        return new CSurface(zoomedSurface);
    }

    SDL_Surface * CSurface::createSurface(int w, int h) {
        auto screen = CApplication::getInstance()->getScreen()._surface;
        auto surface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, screen->format->BitsPerPixel,
            screen->format->Rmask, screen->format->Gmask,
            screen->format->Bmask, screen->format->Amask);
        return surface;
    }
}