#include "KuroConfig.h"
#include "CTime.h"

namespace kuro {
    CTime::CTime(int fps) : _fps(fps) {
    }
    Uint32 CTime::getTicks() {
        return SDL_GetTicks() - _ttime;
    }
    void CTime::start() {
        _ttime = SDL_GetTicks();
    }
    void CTime::wait() {
        if (getTicks() < 1000 / _fps) {
            Uint32 t = (1000 / _fps) - getTicks();
            if (t > 0 && t < 1000)
                SDL_Delay(t);
        }
    }
}