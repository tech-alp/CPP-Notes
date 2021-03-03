#ifndef FIGHTER
#define FIGHTER

// We added with include key word because string is a template class
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Fighter {
public:
    Fighter(std::string name) : mname(std::move(name))
    {
        smvec.push_back(this);
    }
    ~Fighter() {
        if(auto o = std::find(smvec.begin(),smvec.end(),this); o != smvec.end()) {
            smvec.erase(o);
        }
    }
    void ask_for_help()const {
        std::cout << "Ben " << mname << " acil yardim edin.\n";
        for(auto fighter : smvec) {
            if(fighter != this)
                std::cout << fighter->mname << " ";
        }
        std::cout << '\n';
    }

private:
    inline static std::vector<Fighter*> smvec{};
    std::string mname;
};

#endif