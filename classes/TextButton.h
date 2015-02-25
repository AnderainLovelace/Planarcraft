#ifndef _TEXTBUTTON_H_
#define _TEXTBUTTON_H_

#include "kuro/kuro.h"
#include "TextLabel.h"

class TextButton : public kuro::CDrawable {
public:
    TextButton(int width, const kuro::CString & text);

    virtual void draw(int xOffset = 0, int yOffset = 0);

    int getWidth() { return _width; }
    int getHeight() { return _sprMidBack.getSurface().getHeight(); }

    bool getActive() { return _active; }
    void setActive(bool active) { _active = active; }

    void setText(const kuro::CString & text);

    static void loadResource();
    static void freeResource();

protected:
    void centerLabel();

    TextLabel _label;
    bool _active;
    int _width;

    kuro::CSprite _sprMidBack;
    kuro::CSprite _sprMidBackSelected;

    static kuro::CSprite * sprLeft;
    static kuro::CSurface * surMid;
    static kuro::CSprite * sprRight;
    static kuro::CSprite * sprLeftSelected;
    static kuro::CSurface * surMidSelected;
    static kuro::CSprite * sprRightSelected;
};

#endif