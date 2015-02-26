#ifndef _CINPUT_H_
#define _CINPUT_H_

#include "KuroConfig.h"
#include SDL_H_HEADER_FILE
#include "utils/CList.h"

#define KEY_SIZE_MAX        16
#define REPEAT_WAIT_MAX     4

namespace kuro {
    class CInput {
    public:
        enum Key {
            LUp = 0, LDown, LLeft, LRight,
            RUp, RDown, RLeft, RRight,
            Circle, Cross, Square, Triangle,
            LTrigger1, LTrigger2, RTrigger1, RTrigger2
        };
        enum MouseStatus {
            None = 0, Left = 1, Mid = 2, Right = 4
        };

        CInput();

        static CInput & i(); // get singleton instance

        bool trigger(Key key);
        bool repeat(Key key);
        bool quitFlag() { return _quitFlag; }
        void update();

        struct Mouse {
            int x, y, button;
            Mouse(int _x, int _y, int _button) : x(_x), y(_y), button(_button){}
        };

        static Mouse getMouse();

    protected:
        struct KeyTable {
            Uint32  k;
            Key     sym;
            KeyTable() {}
            KeyTable(Uint32 _k, Key _sym) : k(_k), sym(_sym) {}
        };
        CList<KeyTable> _keyList;
        bool _quitFlag;
        bool _keyState[KEY_SIZE_MAX];
        int  _repeatWait;
    };
}

#endif