#include "kuro/KuroConfig.h"
#include "CDrawable.h"

namespace kuro {
    void CDrawable::draw(int xOffset, int yOffset) {
        if (_childs == nullptr)
            return;
        for (auto child : *_childs) {
            auto drawable = CAST(CDrawable *,(child));
            drawable->draw(xOffset + _x, yOffset + _y);
        }
    }
    CPoint CDrawable::getPosition() {
        return CPoint(_x, _y);
    }
}