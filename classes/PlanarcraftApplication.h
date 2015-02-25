#ifndef _PLANARCRAFTAPPLICATION_H_
#define _PLANARCRAFTAPPLICATION_H_

#include "kuro/kuro.h"

class PlanarcraftApplication : public kuro::CApplication {
public:
    PlanarcraftApplication(int w, int h, int bpp, const kuro::CString & title);
    ~PlanarcraftApplication();
    virtual void setVideoMode(int w, int h, int bpp);
    //virtual void go();
};

#endif