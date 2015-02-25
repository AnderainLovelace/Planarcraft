#include "KuroConfig.h"
#include SDL_H_HEADER_FILE
#include "CApplication.h"
#include "CError.h"
#include "CInput.h"
#include "stdlib.h"

namespace kuro {
    CApplication * CApplication::_app = nullptr;
    CApplication::CApplication() 
        : _screen(nullptr), _scene(nullptr), _sceneNext(nullptr) , timer(30){
        initialize();
        registerInstance(this);
        _package.initialize(CMaterialPackage::Method::Local);
    }
    CApplication::~CApplication() {
        quit();
    }
    void CApplication::initialize() {
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    void CApplication::quit() {
        delete _screen;
        SDL_Quit();
    }
    void CApplication::setTitle(const CString & title) {
        SDL_WM_SetCaption(title.cstr(), nullptr);
    }
    void CApplication::setVideoMode(int w, int h, int bpp) {
        _screen = new CScreen(w, h, bpp);
    }

    void CApplication::checkChangeScene() {
        if (_sceneNext == nullptr)
            return;
        if (_scene != nullptr)
            delete _scene;
        _scene = _sceneNext;
        _sceneNext = nullptr;
    }

    void CApplication::go() {
        while (!CInput::i().quitFlag()) {
            checkChangeScene();
            auto scene = getScene();
            if (scene == nullptr)
                break;
                
            timer.start();
            _screen->clear();
            scene->draw();
            scene->update();
            _screen->flip();
            CInput::i().update();

            timer.wait();
        }
    }
}
