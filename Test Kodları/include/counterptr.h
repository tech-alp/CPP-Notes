#ifndef COUNTERPTR_H
#define COUNTERPTR_H

#include "counter.h"

class CounterPtr {
public:
    CounterPtr(Counter* c) : mc(c) {}
    ~CounterPtr()
    {
        if(mc)
            delete mc;
    }

    CounterPtr(const CounterPtr&) = delete;
    CounterPtr& operator=(const CounterPtr&) = delete;

    CounterPtr(CounterPtr&& c): mc(c.mc)
    {
        c.mc = nullptr;
    }

    CounterPtr& operator=(CounterPtr&& c)
    {
        if(this != &c) {
            mc = c.mc;
            c.mc = nullptr;
        }
        return *this;
    }

    Counter& operator*()const
    {
        return *mc;
    }

    Counter* operator->()const
    {
        return mc;
    }

private:
    Counter* mc;
};

#endif