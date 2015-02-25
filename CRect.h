#ifndef _CRECT_H_
#define _CRECT_H_

#include "CPoint.h"

namespace kuro {
    class CRect {
    public:
        CRect();
        CRect(int _x, int _y, int _w, int _h);
        CRect(const CVec2 & s, const CVec2 & e);

        int x;
        int y;
        int w;
        int h;
    };
}

#endif