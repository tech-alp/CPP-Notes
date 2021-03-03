#include <iostream>
#include "mint.h"
#include "myarray.h"
#include "counter.h"
#include "counterptr.h"

#include <array>

void test_mint_class(){
    Mint x,y;
    std::cout << "iki sayi giriniz: ";
    std::cin >> x >> y;
    std::cout << std::boolalpha << (x<y) << std::endl;
    std::cout << std::boolalpha << (x>y) << std::endl;
    std::cout << std::boolalpha << (x<=y) << std::endl;
    std::cout << std::boolalpha << (x>=y) << std::endl;
    std::cout << std::boolalpha << (x==y) << std::endl;
    std::cout << "x + y = " << x + y << '\n';
    std::cout << "x - y = " << x - y << '\n';
    std::cout << "x += y = " << (x += y) << '\n';
    std::cout << "y += x = " << (y += x) << '\n';
    std::cout << "-x = " << -x << '\n';
    std::cout << "-y = " << -y << '\n';
}

void test_myarray()
{
    Myarray array(45);
    for(size_t i = 0; i < array.size(); ++i) {
        array[i] = i;
    }

    for(size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << '\n';

    for(size_t i = 0; i < array.size(); ++i) {
        std::cout << array.at(i) << " ";
    }
    std::cout << '\n';
    
    array[0] = 100;
    std::cout << *array << std::endl;
}

void test_counterptr()
{
    CounterPtr cptr(new Counter);

    std::cout << *cptr << '\n';
    cptr->set_count(50);
    std::cout << cptr->get_count() << '\n';
    std::cout << *cptr << '\n';
    (*cptr).set_count(75);
    std::cout << *cptr << '\n';
}

enum class Weekday {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

Weekday& operator++(Weekday& wd)
{
    return wd = wd == Weekday::Saturday ? Weekday::Sunday : static_cast<Weekday>(static_cast<int>(wd)+1);
}

Weekday operator++(Weekday& wd, int)
{
    Weekday temp{wd};
    ++wd;
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Weekday& wd)
{
    static const char* const pdays[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    return os << pdays[static_cast<int>(wd)];
}

int main() {
    Mint x{-1},y{0};
    std::cout << std::boolalpha << (x<=y) << '\n';
    (void)getchar();
    return 0;
}