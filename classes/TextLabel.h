#ifndef _TEXTLABEL_H_
#define _TEXTLABEL_H_

#include "kuro/kuro.h"

class TextLabel : public kuro::CDrawable{
public:
    TextLabel(const kuro::CString & text);
    virtual void draw(int xOffset = 0, int yOffset = 0);

    int getWidth();
    int getHeight();

    kuro::CString getText() { return _text; }
    void setText(const kuro::CString & text) { _text = text; }

    static void loadResource();
    static void freeResource();

protected:
    kuro::CString _text;

    static kuro::CSprite * _sprCharset;
};

#endif