#include "kuro/KuroConfig.h"
#include "kuro/CApplication.h"
#include "CSprite.h"

namespace kuro {
    CSprite::CSprite()
        : _csurface(nullptr), _autoRelease(true), _clipRect(nullptr) {
    }
    CSprite::CSprite(const CString & fileName)
        : _csurface(new CSurface(fileName)), _autoRelease(true), _clipRect(nullptr) {
    }
    CSprite::~CSprite() {
        // auto release
        if (_autoRelease && _csurface != nullptr)
            delete _csurface;
        if (_clipRect != nullptr)
            delete _clipRect;
    }

    void CSprite::setSurface(CSurface * csurface) {
        // auto release
        if (_autoRelease && _csurface != nullptr)
            delete _csurface;
        _csurface = csurface;
    }

    void CSprite::draw(int xOffset, int yOffset) {
        if (_csurface == nullptr)
            return;
        _csurface->applyTo(CApplication::getInstance()->getScreen(), xOffset + _x, yOffset + _y, _clipRect);
    }
}