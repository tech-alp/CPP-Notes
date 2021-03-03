#ifndef MINT_H
#define MINT_H

#include <iosfwd>

class Mint {
public:
    Mint();
    Mint(int);

    friend bool operator<(const Mint& x, const Mint& y);

    friend std::ostream& operator<<(std::ostream&, const Mint&);
    friend std::istream& operator>>(std::istream&, Mint&);

    Mint& operator++();
    Mint operator++(int);
    
    Mint& operator--();
    Mint operator--(int);

    Mint& operator+=(const Mint& x);
    Mint& operator-=(const Mint& x);

    Mint operator+()const;
    Mint operator-()const;
    
private:
    int mval;

};

inline Mint operator+(const Mint& x, const Mint& y) {
    return Mint(x)+=y;
}

inline Mint operator-(const Mint& x, const Mint& y) {
    return Mint(x)-=y;
}

inline bool operator<=(const Mint& x, const Mint& y)
{
    return !(y<x);
}

inline bool operator==(const Mint& x, const Mint& y)
{
    return !(x<y) && !(y<x);
}

inline bool operator>(const Mint& x, const Mint& y)
{
    return y<x;
}

inline bool operator>=(const Mint& x, const Mint& y)
{
    return !(x<y);
}

#endif