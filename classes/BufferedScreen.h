#ifndef _BUFFEREDSCREEN_H_
#define _BUFFEREDSCREEN_H_

#include "kuro/kuro.h"

class BufferedScreen : public kuro::CScreen {
public:
    BufferedScreen(int w, int h, int bpp, int zoom);
    ~BufferedScreen();
    virtual void flip();
    virtual void clear();
    virtual int getWidth() override { return _width; }
    virtual int getHeight() override { return _height; }
    void createBuffer(); // 因为 CSurface::createSurface引用了
                         // CApplication::_screen，所以要在CApplication
                         // 获取_screen之后再生成缓存，不能在构造函数里调用
protected:
    kuro::CSurface * _buffer;
    int _zoom;
    int _width;
    int _height;

    virtual SDL_Surface * getSDLSurface() { return _buffer->getSDLSurface(); }
};

#endif