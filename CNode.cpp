#include "KuroConfig.h"
#include "CNode.h"

namespace kuro {
    CNode::CNode() : _childs(nullptr) {
    }

    CNode::~CNode() {
        if (_childs != nullptr) {
            for (CNode * child : *_childs) {
                delete child;
            }
            delete[] _childs;
        }
    }

    void CNode::update() {
        if (scheduler)
            scheduler();
        if (_childs != nullptr) {
            for (CNode * child : *_childs) {
                child->update();
            }
        }
    }

    void CNode::addChild(CNode * child) {
        if (child == nullptr)
            return;
        if (_childs == nullptr)
            _childs = new CList<CNode *>();
        _childs->push_back(child);
    }

    void CNode::removeChild(CNode * child) {
        if (child == nullptr)
            return;
        for (CList<CNode *>::iterator it = _childs->begin(); it != _childs->end(); ++it) {
            if (*it == child) {
                _childs->erase(it);
            }
        }
    }
}
