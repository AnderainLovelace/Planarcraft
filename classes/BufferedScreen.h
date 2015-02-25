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
    void createBuffer(); // ��Ϊ CSurface::createSurface������
                         // CApplication::_screen������Ҫ��CApplication
                         // ��ȡ_screen֮�������ɻ��棬�����ڹ��캯�������
protected:
    kuro::CSurface * _buffer;
    int _zoom;
    int _width;
    int _height;

    virtual SDL_Surface * getSDLSurface() { return _buffer->getSDLSurface(); }
};

#endif