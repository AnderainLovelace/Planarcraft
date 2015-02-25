#ifndef _CTIME_H_
#define _CTIME_H_

#include "KuroConfig.h"
#include SDL_H_HEADER_FILE

namespace kuro {
    class CTime {
    public:
        CTime(int fps);
        void start();
        void wait();
    protected:
        int _fps;
        Uint32 _ttime;

        Uint32 getTicks();
    };
}

#endif