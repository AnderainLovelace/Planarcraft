#include "TextButton.h"

using namespace kuro;

CSprite * TextButton::sprLeft = nullptr;
CSurface * TextButton::surMid = nullptr;
CSprite * TextButton::sprRight = nullptr;
CSprite * TextButton::sprLeftSelected = nullptr;
CSurface * TextButton::surMidSelected = nullptr;
CSprite * TextButton::sprRightSelected = nullptr;

void TextButton::loadResource() {
    sprLeft = new CSprite("button_ns_left.bmp");
    surMid = new CSurface("button_ns_mid.bmp");
    sprRight = new CSprite("button_ns_right.bmp");
    sprLeftSelected = new CSprite("button_s_left.bmp");
    surMidSelected = new CSurface("button_s_mid.bmp");
    sprRightSelected = new CSprite("button_s_right.bmp");
}
void TextButton::freeResource() {
    delete sprLeft;
    delete surMid;
    delete sprRight;
    delete sprLeftSelected;
    delete surMidSelected;
    delete sprRightSelected;
}

TextButton::TextButton(int width, const CString & text) : _label(text), _width(width), _active(false) {
    double xZoom = (double)(width - sprLeft->getSurface().getWidth() - sprRight->getSurface().getWidth()) / (surMid->getWidth());
    _sprMidBack.setSurface(surMid->rotozoom(xZoom,1.0,0,false));
    _sprMidBackSelected.setSurface(surMidSelected->rotozoom(xZoom, 1.0, 0, false));

    centerLabel();
}

void TextButton::centerLabel() {
    _label.setX((getWidth() - _label.getWidth()) / 2);
    _label.setY((getHeight() - _label.getHeight()) / 2);
}

void TextButton::draw(int xOffset, int yOffset) {
    CSprite *l, *m, *r;
    int x = _x + xOffset, y = _y + yOffset;
    if (_active) {
        l = sprLeftSelected;
        m = &_sprMidBackSelected;
        r = sprRightSelected;
    }
    else {
        l = sprLeft;
        m = &_sprMidBack;
        r = sprRight;
    }
    l->setPosition(0, 0);
    m->setPosition(l->getSurface().getWidth(), 0);
    r->setPosition(l->getSurface().getWidth() + m->getSurface().getWidth(), 0);
    l->draw(x, y); m->draw(x, y); r->draw(x, y);
    _label.draw(x, y);
}

void TextButton::setText(const CString & text) {
    _label.setText(text);
    centerLabel();
}