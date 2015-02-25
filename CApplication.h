#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include "utils/CString.h"
#include "drawable/CScreen.h"
#include "drawable/CScene.h"
#include "CMaterialPackage.h"
#include "CTime.h"

namespace kuro {
    class CApplication {
    public:
        CApplication();
        ~CApplication();

        void go();

        virtual void setTitle(const CString & title);
        virtual void setVideoMode(int width, int height, int bpp);

        virtual CScreen & getScreen() { return *_screen; }

        CScene * getScene() { return _scene; }
        CScene * setScene(CScene * scene) { return _sceneNext = scene; }

        CMaterialPackage & getPackage() { return _package; }

        static CApplication * getInstance() { return _app; }

        static int getScreenWidth() { return _app->_screen->getWidth(); }
        static int getScreenHeight() { return _app->_screen->getHeight(); }

    protected:
        void initialize();
        void quit();

        CScreen * _screen;

        static void registerInstance(CApplication * app) { _app = app; }
        static CApplication * _app;

        CScene * _scene;
        CScene * _sceneNext;
        void checkChangeScene();

        CMaterialPackage _package;

        CTime timer;
    };
}

#endif