#include "PlanarcraftApplication.h"
#include "TitleScene.h"
#include "BufferedScreen.h"
#include "TextLabel.h"
#include "TextButton.h"

PlanarcraftApplication::PlanarcraftApplication(int w, int h, int bpp, const kuro::CString & title)
    : CApplication() {
    setVideoMode(w, h, bpp);
    setTitle(title);

    TextLabel::loadResource();
    TextButton::loadResource();

    setScene(new TitleScene());
}

PlanarcraftApplication::~PlanarcraftApplication() {
    TextLabel::freeResource();
    TextButton::freeResource();
}

void PlanarcraftApplication::setVideoMode(int w, int h, int bpp) {
#ifndef ___NDLESS___
    BufferedScreen * bufferedScreen = new BufferedScreen(w, h, bpp, 2);
    _screen = bufferedScreen;
    bufferedScreen->createBuffer();
#else
    kuro::CApplication::setVideoMode(w, h, bpp);
#endif
}