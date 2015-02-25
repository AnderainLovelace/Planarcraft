#include "CInput.h"

namespace kuro {
    // initialize
    CInput::CInput() : _quitFlag(false), _repeatWait(0) {
        for (int i = 0; i < KEY_SIZE_MAX; ++i) {
            _keyState[i] = false;
        }
        _keyList.push_back(KeyTable(SDLK_w, LUp));
        _keyList.push_back(KeyTable(SDLK_s, LDown));
        _keyList.push_back(KeyTable(SDLK_a, LLeft));
        _keyList.push_back(KeyTable(SDLK_d, LRight));

        _keyList.push_back(KeyTable(SDLK_i, Triangle));
        _keyList.push_back(KeyTable(SDLK_k, Cross));
        _keyList.push_back(KeyTable(SDLK_j, Square));
        _keyList.push_back(KeyTable(SDLK_l, Circle));

        _keyList.push_back(KeyTable(SDLK_q, LTrigger2));
        _keyList.push_back(KeyTable(SDLK_e, RTrigger2));
        _keyList.push_back(KeyTable(SDLK_u, LTrigger1));
        _keyList.push_back(KeyTable(SDLK_o, LTrigger1));

        _keyList.push_back(KeyTable(SDLK_UP, RUp));
        _keyList.push_back(KeyTable(SDLK_DOWN, RDown));
        _keyList.push_back(KeyTable(SDLK_LEFT, RLeft));
        _keyList.push_back(KeyTable(SDLK_RIGHT, RRight));
    }
    // get singleton instance
    CInput & CInput::i() {
        static CInput instance;
        return instance;
    }
    // update for chcek key status
    void CInput::update() {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                _quitFlag = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                int i = 0, k = event.key.keysym.sym;
                if (k == SDLK_ESCAPE) {
                    _quitFlag = true;
                    return;
                }
#ifdef ___NDLESS___
                /* 如果有在NSPIRE环境下，添加调节对比度功能 */
                if (k == SDLK_a)
                    ContrastInc();
                if (k == SDLK_b)
                    ContrastDec();
#endif
                for (auto & t : _keyList) {
                    if (k == t.k) {
                        _keyState[t.sym] = true;
                        _repeatWait = REPEAT_WAIT_MAX;
                        break;
                    }
                }
            }
            else if (event.type == SDL_KEYUP) {
                for (auto & t : _keyList) {
                    if (event.key.keysym.sym == t.k) {
                        _keyState[t.sym] = false;
                        break;
                    }
                }
            }
        }
    }
    /*!
    * @brief 判断按键是否按下
    * @param gkey 内部按键代码
    * @return BOOL 指定的键按下时返回TRUE，否则返回FALSE
    *
    * @note 只检测第一次按下
    */
    bool CInput::trigger(Key sym) {
        if (_keyState[sym]) {
            _keyState[sym] = false;
            return true;
        }
        return false;
    }
    /*!
    * @brief 判断按键是否按下
    * @param gkey 内部按键代码
    * @return BOOL 指定的键按下时返回TRUE，否则返回FALSE
    *
    * @note 重复检测按键的状态
    */
    bool CInput::repeat(Key sym) {
        if (_keyState[sym]) {
            if (_repeatWait == REPEAT_WAIT_MAX) {
                _repeatWait--;
                return true;
            }
            else if (_repeatWait > 0) {
                _repeatWait--;
                return false;
            }
            return true;
        }
        return false;
    }
}