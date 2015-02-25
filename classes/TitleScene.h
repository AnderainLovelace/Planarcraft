#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "kuro/kuro.h"
#include "TextButton.h"

class TitleScene : public kuro::CScene {
public:
    TitleScene();
    ~TitleScene();
    virtual void initialize() override;

protected:
    kuro::CSprite * sprLogo;
    kuro::CSprite * sprBack0;
    kuro::CSprite * sprBack1;

    TextButton * button[3];

    int _index;
};

#endif