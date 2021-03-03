#include "myarray.h"
#include <cstring>
#include <iostream>

Myarray::Myarray(int size) : msize(size), mp(new int[size])
{
    std::memset(mp,0,msize * sizeof(int));
}

Myarray::~Myarray()
{
    delete[] mp;
}

int& Myarray::operator[](int idx)
{
    return mp[idx];
}

const int& Myarray::operator[](int idx)const
{
    return mp[idx];
}


int& Myarray::operator*()const
{
    return *mp;
}

int Myarray::size()const
{
    return msize;
}

int& Myarray::at(int idx)
{
    if(idx > msize)
    {
        std::cout << "Dizinin boyutundan daha büyük yere eriştiniz.\n";
        exit(EXIT_FAILURE);
    }
    return mp[idx];

}

const int& Myarray::at(int idx)const
{
    if(idx > msize)
    {
        std::cout << "Dizinin boyutundan daha büyük yere eriştiniz.\n";
        exit(EXIT_FAILURE);
    }
    return mp[idx];
}