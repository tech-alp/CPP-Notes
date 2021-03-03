#ifndef MYARRAY_H
#define MYARRAY_H

class Myarray {
public:
    Myarray(int = 0);
    ~Myarray();

    int& operator[](int index);
    const int& operator[](int index)const;

    int& operator*()const;

    int size()const;

    int& at(int idx);
    const int& at(int idx)const;

private:
    int msize;
    int* mp;

};

#endif