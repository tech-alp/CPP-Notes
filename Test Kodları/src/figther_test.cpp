#include <iostream>
#include "fighter.h"

int main() {
    Fighter f1("Enes");    
    Fighter* f2 = new Fighter("Ahmet");
    auto f3 = new Fighter("Tayfur");
    Fighter f4("Ayse");
    delete f2;

    f1.ask_for_help();

    (void)getchar();
    return 0;
}