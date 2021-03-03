#ifndef COUNTER_H
#define COUNTER_H

#include <ostream>

class Counter {
public:
    Counter(int count = 0) : mcount(count) {}
    ~Counter() {}

    friend std::ostream& operator<<(std::ostream& out, const Counter& c)
    {
        out << c.mcount;
        return out;
    }

    Counter& operator++()
    {
        ++mcount;
        return *this;
    }

    Counter operator++(int)
    {
        Counter temp(*this);
        ++(*this);
        return temp;
    }

    void set_count(int count)
    {
        mcount = count;
    }

    int get_count()const
    {
        return mcount;
    }

private:
    int mcount;
};

#endif