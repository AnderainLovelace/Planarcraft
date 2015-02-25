#include "TitleScene.h"

using namespace kuro;

TitleScene::TitleScene() {
    initialize();
}

TitleScene::~TitleScene() {

}

void TitleScene::initialize() {
    sprBack0 = new CSprite();
    sprBack0->setSurface(new CSurface("title_back_0.jpg"));
    sprBack0->setPosition(0, 0);
    sprBack0->scheduler = [&]() {
        sprBack0->setX(sprBack0->getX() + 1);
        if (sprBack0->getX() >= CApplication::getScreenWidth())
            sprBack0->setX(-CApplication::getScreenWidth());
    };
    addChild(sprBack0);

    sprBack1 = new CSprite();
    sprBack1->setSurface(new CSurface("title_back_1.jpg"));
    sprBack1->setPosition(-CApplication::getScreenWidth(), 0);
    sprBack1->scheduler = [&]() {
        sprBack1->setX(sprBack1->getX() + 1);
        if (sprBack1->getX() >= CApplication::getScreenWidth())
            sprBack1->setX(-CApplication::getScreenWidth());
    };
    addChild(sprBack1);

    sprLogo = new CSprite();
    sprLogo->setSurface(new CSurface("logo.png"));
    sprLogo->setPosition((CApplication::getScreenWidth() - sprLogo->getSurface().getWidth()) / 2, 32);
    addChild(sprLogo);

    static const char * menu[] = { "New Game", "Load Game", "Option" };
    for (int i = 0; i < 3; ++i) {
        button[i] = new TextButton(160, menu[i]);
        button[i]->setPosition(80, 130 + 30 * i);
        addChild(button[i]);
    }

    _index = 0;
    button[_index]->setActive(true);
    scheduler = [&]() {
        if (CInput::i().trigger(CInput::LUp)) {
            button[_index]->setActive(false);
            if (--_index < 0) _index = 2;
            button[_index]->setActive(true);
        }
        else if (CInput::i().trigger(CInput::LDown)) {
            button[_index]->setActive(false);
            if (++_index >= 3) _index = 0;
            button[_index]->setActive(true);
        }
    };

    auto label = new TextLabel("Back to Uiharu 2014");
    label->setPosition(0, 232);
    addChild(label);
}
