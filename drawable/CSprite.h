#ifndef _CSPRITE_H_
#define _CSPRITE_H_

#include "CDrawable.h"
#include "CSurface.h"
#include "kuro/CPoint.h"

namespace kuro {
    class CSprite : public CDrawable {
    public:
        CSprite(const CString & fileName);
        CSprite();
        ~CSprite();

        virtual void draw(int xOffset = 0, int yOffset = 0);
        
        bool setAutoRelease(bool autoRelease) { return _autoRelease = autoRelease; }

        CSurface & getSurface() { return *_csurface; }
        void setSurface(CSurface * csurface);

        CRect * getClipRect() { return _clipRect; }
        void setClipRect(CRect * clipRect) { _clipRect = clipRect; }

    protected:
        CSurface * _csurface;
        CRect * _clipRect;
        bool _autoRelease;
    };
}

#endif 