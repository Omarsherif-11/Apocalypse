#ifndef MILESTONE1_TEAM16_PISTOL_H
#define MILESTONE1_TEAM16_PISTOL_H

#include "Gun.h"
#include "Hero.h"

class Pistol : public Gun
{
public:
    Pistol();
    Pistol(const string &name);
    virtual ~Pistol();
    void useSpecial(Hero &h1, Object *** map);
};



#endif //MILESTONE1_TEAM16_PISTOL_H
