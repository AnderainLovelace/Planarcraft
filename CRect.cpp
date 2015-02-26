#include "KuroConfig.h"
#include "CRect.h"

namespace kuro {
    CRect::CRect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
    CRect::CRect(const CVec2 & s, const CVec2 & e) : x(s.x), y(s.y), w(e.x), h(e.y) {}
    CRect::CRect() : x(0), y(0), w(0), h(0) {}

    bool CRect::contian(const CPoint & p) {
        return (p.x >= x && p.y >= y && p.x <= x + w && p.y <= y + h);
    }
}