#ifndef MILESTONE1_TEAM16_RIFLE_H
#define MILESTONE1_TEAM16_RIFLE_H

#include "Gun.h"

class Rifle : public Gun

{
public:
    Rifle();
    Rifle(const string &name);
    virtual ~Rifle();

    void useSpecial(Hero &h1, Object ***map);
};



#endif //MILESTONE1_TEAM16_RIFLE_H
