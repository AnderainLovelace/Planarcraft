#ifndef _CSCENE_H_
#define _CSCENE_H_

#include "CDrawable.h"

namespace kuro {
    class CScene : public CDrawable {
    public:
        CScene();
        virtual ~CScene();
        virtual void initialize() = 0;
    protected:
    };
}

#endif