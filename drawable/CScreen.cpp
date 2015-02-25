#include "kuro/KuroConfig.h"
#include "CScreen.h"

namespace kuro {
    CScreen::CScreen(int w, int h, int bpp) {
        _surface = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE);
    }
    CScreen::CScreen(CScreen * screen) {
        _surface = screen->_surface;
    }
    CScreen::~CScreen() {
        //do nothing
        _surface = nullptr;
    }
    void CScreen::clear() {
        fill(0x000000);
    }
    void CScreen::flip() {
        SDL_Flip(_surface);
    }
}