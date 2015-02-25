#ifndef _CNODE_H_
#define _CNODE_H_

#include "utils/CList.h"
#include <functional>

namespace kuro {
    class CNode {
    public:
        CNode();
        virtual ~CNode();

        void addChild(CNode * child);
        void removeChild(CNode * child);

        std::function<void(void)> scheduler;
        void update();

    protected:
        CList<CNode *> * _childs;
    };
}

#endif