#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton {
public:
    static Singleton& get_singleton()
    {
        static Singleton s;
        return s;
    }

    void get_class_name()const
    {
        std::cout << "Singleton\n";
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {std::cout << "Default constructor.\n";}
    ~Singleton() {std::cout << "Destructor.\n";}
}; 

#endif