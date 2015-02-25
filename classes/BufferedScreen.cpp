#include "BufferedScreen.h"
#include "kuro/sdl/rotozoom.h"

BufferedScreen::BufferedScreen(int w, int h, int bpp, int zoom) 
    : CScreen(w * zoom, h * zoom, bpp), _zoom(zoom), _width(w), _height(h) {
}

BufferedScreen::~BufferedScreen() {
    delete _buffer;
}

void BufferedScreen::clear() {
    _buffer->fill(0x000000);
}

void BufferedScreen::flip() {
    CSurface * zoomSurface = _buffer->zoom(_zoom, _zoom, false);
    SDL_BlitSurface(zoomSurface->getSDLSurface(), nullptr, this->_surface, nullptr);
    delete zoomSurface;

    CScreen::flip();
}

void BufferedScreen::createBuffer() {
    _buffer = new CSurface(_width, _height, 0);
}