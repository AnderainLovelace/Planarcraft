#ifndef _CLIST_H_
#define _CLIST_H_

namespace kuro {
    template <class T>
    class CList
    {
    protected:
        class CNode
        {
        public:
            CNode(const T& t = T(), CNode* p = 0, CNode* n = 0) :val(t), prev(p), next(n)
            {
                if (prev == 0) prev = this;
                if (next == 0) next = this;
            }
            T val;
            CNode* prev, *next;
        };
    public:
        class iterator
        {
        public:
            friend class CList < T > ;
            iterator() {}
            iterator(CNode* n) : node(n){}
            iterator(const iterator& L) : node(L.node) {}
            ~iterator() {}
            T& operator * () { return node->val; }
            iterator& operator = (const iterator& it) { node = it.node; }
            bool operator == (const iterator& it) { return it.node == node; }
            bool operator != (const iterator& it) { return it.node != node; }
            iterator operator ++ (int) // 后缀iter++  
            {
                iterator it(node);
                node = node->next;
                return it;
            }
            iterator& operator ++ () // 前缀++iter  
            {
                node = node->next;
                return *this;
            }
            iterator operator -- (int)
            {
                iterator it(node);
                node = node->prev;
                return it;
            }
            iterator& operator -- ()
            {
                node = node->prev;
                return *this;
            }
        protected:
        private:
            CNode* node;
        };

        CList();
        CList(const CList& L);
        CList(int n);
        CList(int n, const T& t);
        CList(iterator& first, iterator& last);
        ~CList();
        CList& operator = (const CList& L);

        int getSize() const { return _size; }
        bool empty() const { return _size == 0; }
        T& front();
        T& back();

        iterator begin();
        iterator end(); //返回虚拟头指针，不指向任何有效元素  
        void push_front(const T& t);
        void push_back(const T& t);
        void pop_front();
        void pop_back();

        iterator insert(iterator& it, const T& t);
        iterator insert(iterator& it, int n, const T& t);

        void erase(iterator& it);
        void erase(iterator& first, iterator& last);
        void clear();
        void splice(iterator& it, CList& list, iterator& first);
    private:
        CNode* _head; //虚拟头指针  
        size_t _size;
    };

    template <class T> CList<T>::CList() :_size(0)
    {
        _head = new CNode;
    }

    template <class T> CList<T>::CList(const CList& list) : _size(list._size)
    {
        _head = new CNode();
        CNode* temp = _head;
        for (CNode* p = list._head->next; p != list._head; p = p->next)
        {
            temp = temp->next = new CNode(p->val, temp, _head);
        }
        _head->prev = temp;
    }

    template <class T> CList<T>::CList(int n) :_size(n)
    {
        _head = new CNode;
        CNode* temp = _head;
        for (int i = 0; i < n; i++)
        {
            temp = temp->next = new CNode(T(), temp, _head);
        }
    }

    template <class T> CList<T>::CList(int n, const T& t) :_size(n)
    {
        _head = new CNode();
        CNode* temp = _head;
        for (int i = 0; i < n; i++)
        {
            temp = temp->next = new CNode(t, temp, _head); //往temp和head中间插入新节点  
        }
        _head->prev = temp;
    }

    template <class T> CList<T>::CList(iterator& first, iterator& last)
    {
        _head = new CNode;
        CNode* temp = _head;
        for (iterator p = first; first != last; last++)
        {
            temp = temp->next = new CNode(p.node->val, temp, _head);
            ++_size;
        }
    }

    template <class T> CList<T>::~CList()
    {
        CNode* temp = _head->next;
        while (temp != _head)
        {
            CNode* p = temp;
            temp = temp->next;
            delete p;
        }
        delete _head;
    }

    template <class T> CList<T>& CList<T>::operator = (const CList& L)
    {
        _size = L._size;
        clear();
        _head = new CNode;
        CNode* temp = _head;
        CNode* p = L._head->next;
        while (p != L._head)
        {
            temp = temp->next = new CNode(p->val, temp, _head);
            p = p->next;
        }
    }

    template <class T> T& CList<T>::front()
    {
        return _head->next->val;
    }

    template <class T> T& CList<T>::back()
    {
        return _head->prev->val;
    }

    template <class T> typename CList<T>::iterator CList<T>::begin() //注意：这里必须加typename，否则VC无法编译通过！  
    {
        iterator temp(_head->next);
        return temp;
    }

    template <class T> typename CList<T>::iterator CList<T>::end()
    {
        iterator temp(_head);
        return temp;
    }

    template <class T> void CList<T>::push_front(const T& t)
    {
        _head->next = _head->next->prev = new CNode(t, _head, _head->next);
        ++_size;
    }

    template <class T> void CList<T>::push_back(const T& t)
    {
        CNode* temp = _head->prev;
        temp = temp->next = new CNode(t, temp, _head); //这里往temp和head中间插入新节点，也可以相反  
        _head->prev = temp;
        ++_size;
    }

    template <class T> void CList<T>::pop_front()
    {
        if (_size > 0)
        {
            CNode* temp = _head->next;
            _head->next = temp->next;
            temp->next->prev = _head;
            delete temp;
            --_size;
        }
        return;
    }

    template <class T> void CList<T>::pop_back()
    {
        if (_size > 0)
        {
            CNode* temp = _head->prev;
            _head->prev = temp->prev;
            temp->prev->next = _head;
            delete temp;
            --_size;
        }
        return;
    }

    template <class T>
    typename CList<T>::iterator CList<T>::insert(iterator& it, const T& t) //在it前插入元素  
    {
        CNode* temp = it.node->prev;
        temp = temp->next = new CNode(t, temp, it.node);
        it.node = it.node->prev;

        ++_size;
        iterator LIter(temp);
        return LIter;
    }

    template <class T>
    typename CList<T>::iterator CList<T>::insert(iterator& it, int n, const T& t)
    {
        CNode* p = it.node;
        CNode* q = p->prev;
        for (int i = 0; i < n; i++)
        {
            q = q->next = new CNode(t, q, p);
            ++_size;
        }
        p->prev = q;
        it.node = p;

        iterator LIter(p);
        return LIter;
    }

    template <class T>
    void  CList<T>::erase(iterator& it)
    {
        if (_size == 0) return;
        CNode* temp = it.node;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        it.node = temp->next;
        delete temp;
        --_size;
    }

    template <class T>
    void CList<T>::erase(iterator& first, iterator& last) //last不会被删除  
    {
        first.node->prev->next = last.node;
        last.node->prev = first.node->prev;

        CNode* temp = first.node;
        CNode* p = first.node->next;
        while (temp != last.node)
        {
            delete temp;
            temp = p;
            p = p->next;
            --_size;
        }
    }

    template <class T>
    void CList<T>::clear()
    {
        while (_head->next != _head)
        {
            pop_back();
        }
    }

    template <class T>
    void CList<T>::splice(iterator& it, CList& L, iterator& first) //从其他list中抽取元素first至it前  
    {
        CNode* p = it.node;
        CNode* q = first.node;

        q->prev->next = q->next; //先将first断开  
        q->next->prev = q->prev;

        q->prev = p; //再将first与it连接，原则：先右后左  
        q->next = p->next;

        p->next->prev = q;
        p->next = q;

        ++_size;
        --L._size;
    }
}

#endif