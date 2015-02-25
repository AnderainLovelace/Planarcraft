#ifndef _CSCREEN_H_
#define _CSCREEN_H_

#include "CSurface.h"

namespace kuro {
    class CScreen : public CSurface {
    public:
        CScreen(int w, int h, int bpp);
        CScreen(CScreen * screen); // ×ªÒÆÆÁÄ»¿ØÖÆÈ¨
        virtual ~CScreen();
        virtual void clear();
        virtual void flip();
    };
}

#endif