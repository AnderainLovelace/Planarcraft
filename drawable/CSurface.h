#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include "kuro/KuroConfig.h"
#include SDL_H_HEADER_FILE

#include "CDrawable.h"
#include "kuro/CRect.h"

#include "kuro/utils/CString.h"

namespace kuro {
    class CSurface {
    public:
        CSurface(int w, int h, Uint32 color);
        CSurface(const CString & fileName);
        CSurface();
        virtual ~CSurface();

        virtual void applyTo(CSurface & destination, int x, int y, CRect * clipRect = nullptr);
        inline CVec2 getSize();

        void setPixel(int x, int y, Uint32 pixel);
        void fill(Uint32 color);

        virtual int getWidth() { return _surface->w; }
        virtual int getHeight() { return _surface->h; }

        CSurface * rotozoom(double xZoom, double yZoom, double angle, bool smooth);
        CSurface * zoom(double xZoom, double yZoom, bool smooth);
        virtual SDL_Surface * getSDLSurface() { return _surface; }

    protected:
        CSurface(SDL_Surface * surface);
        SDL_Surface * _surface;

        SDL_Surface * createSurface(int w, int h);
        
    };
}

#endif