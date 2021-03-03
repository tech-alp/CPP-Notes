#include <iostream>
#include <vector>
#include <string>

struct Onestruct {
    std::vector<std::string> vs;
    Onestruct(std::vector<std::string> in)
    {
        vs.swap(in);
    }
};

void func(int* ptr){
    std::cout << "func(int*)\n";
}
void func(const int* ptr){
    std::cout << "func(const int*)\n";
}

int main() 
{
    int a = 0;
    func(&a);
    return 0;
}