#include "KuroConfig.h"
#include "CPoint.h"

namespace kuro {
    CPoint::CPoint(int _x, int _y) : x(_x), y(_y) {}
    CPoint::CPoint(const CPoint & point) : x(point.x), y(point.y) {}
    CPoint::CPoint() : x(0), y(0) {}
}