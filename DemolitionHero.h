#ifndef MILESTONE1_TEAM16_DEMOLITIONHERO_H
#define MILESTONE1_TEAM16_DEMOLITIONHERO_H

#include "Hero.h"

class DemolitionHero: public Hero
{
private:
    Gun * gun2;
public:
    DemolitionHero();
    DemolitionHero(double xPos, double yPos, double health,  Gun *gun,  Gun *gun2);
    virtual ~DemolitionHero();

     Gun * getGun2() const;
    void setGun2( Gun *gun2);

    void useSpecial();
};



#endif //MILESTONE1_TEAM16_DEMOLITIONHERO_H
