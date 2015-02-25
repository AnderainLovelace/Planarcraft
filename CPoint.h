#ifndef _CPOINT_H_
#define _CPOINT_H_

namespace kuro {
    class CPoint {
    public:
        CPoint(int x, int y);
        CPoint(const CPoint & point);
        CPoint();
        
        int x;
        int y;
    };

    typedef CPoint CVec2;
}

#endif