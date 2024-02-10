#ifndef MILESTONE1_TEAM16_HERO_H
#define MILESTONE1_TEAM16_HERO_H

#include "Character.h"
#include "Gun.h"
#include "Ammo.h"
#include "Monster.h"
#include "Potion.h"
class Gun;
class Hero: public Character
{
private:
    Gun* gun;
public:
    Hero(Gun *gun);
    Hero(char type, int xPos, int yPos, double health,  Gun *gun);
    virtual ~Hero();

    Gun *getGun() const;
    void setGun( Gun *gun);

    friend ostream& operator<<(ostream& os, const Hero& hero);
    Hero* operator +(const Ammo& ammo);
    Hero* operator +(const Potion& potion);
    Hero* operator -(Monster* mons);

    virtual void useSpecial();
};



#endif //MILESTONE1_TEAM16_HERO_H
