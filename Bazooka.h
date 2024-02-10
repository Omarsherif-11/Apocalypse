#ifndef MILESTONE1_TEAM16_BAZOOKA_H
#define MILESTONE1_TEAM16_BAZOOKA_H

#include "Gun.h"

class Bazooka: public Gun
{
public:
    Bazooka();
    Bazooka(const string &name);
    virtual ~Bazooka();

    void useSpecial(Hero &h1, Object ***map);
};



#endif //MILESTONE1_TEAM16_BAZOOKA_H
