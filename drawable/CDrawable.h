#ifndef _CDRAWABLE_H_
#define _CDRAWABLE_H_

#include "../CNode.h"
#include "../CPoint.h"

namespace kuro {
    class CDrawable : public CNode {
    public:
        CDrawable() : _x(0), _y(0) {}
        virtual ~CDrawable() {}

        virtual void draw(int xOffset = 0, int yOffset = 0);

        CPoint getPosition();
        void setPosition(int x, int y) { _x = x, _y = y; }
        void setPosition(const CPoint & p) { _x = p.x, _y = p.y; }

        virtual void setX(int x) { _x = x; }
        virtual void setY(int y) { _y = y; }
        virtual int getX() { return _x; }
        virtual int getY() { return _y; }

    protected:
        int _x;
        int _y;
    };
}

#endif