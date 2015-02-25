#include "TextLabel.h"

using namespace kuro;

static const int FontWidth = 8;
static const int FontHeight = 8;
static const int FontRealWidth = 6;

CSprite * TextLabel::_sprCharset = nullptr;

TextLabel::TextLabel(const CString & text) : _text(text) {
}

void TextLabel::loadResource() {
    _sprCharset = new CSprite();
    _sprCharset->setSurface(new CSurface("ascii.png"));
    _sprCharset->setClipRect(new CRect(0, 0, FontWidth, FontHeight));
}
void TextLabel::freeResource() {
    if (_sprCharset != nullptr)
        delete _sprCharset;
}

int TextLabel::getWidth() {
    return FontRealWidth * _text.size();
}
int TextLabel::getHeight() {
    return FontHeight;
}

void TextLabel::draw(int xOffset, int yOffset) {
    const char * str = _text.cstr();
    int x = _x + xOffset, y = _y + yOffset;
    CRect * rect = _sprCharset->getClipRect();
    while (*str) {
        rect->x = *str % 16 * FontWidth;
        rect->y = (*str) / 16 * FontHeight;

        _sprCharset->setPosition(x, y);
        _sprCharset->draw();

        ++str;
        x += FontRealWidth;
    }
}