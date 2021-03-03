#include "mint.h"
#include <iostream>

Mint::Mint() {}

Mint::Mint(int val) : mval(val) {}

std::ostream& operator<<(std::ostream& out, const Mint& m)
{
    out << m.mval;
    return out;
}
std::istream& operator>>(std::istream& in, Mint& m)
{
    in >> m.mval;
    return in;
}

bool operator<(const Mint& x, const Mint& y) {
    return x.mval < y.mval;
}

Mint& Mint::operator++()
{
    ++mval;
    return *this;
}

Mint Mint::operator++(int)
{
    Mint temp(*this);
    ++(*this);
    return temp;
}

Mint& Mint::operator--()
{
    --mval;
    return *this;
}

Mint Mint::operator--(int)
{
    Mint temp(*this);
    --(*this);
    return temp;
}

Mint Mint::operator+()const
{
    return *this;
}

Mint Mint::operator-()const
{
    return Mint{-mval};
}

Mint& Mint::operator+=(const Mint& x)
{
    mval += x.mval;
    return *this;
}

Mint& Mint::operator-=(const Mint& x)
{
    mval -= x.mval;
    return *this;
}