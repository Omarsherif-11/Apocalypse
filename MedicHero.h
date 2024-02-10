#ifndef MILESTONE1_TEAM16_MEDICHERO_H
#define MILESTONE1_TEAM16_MEDICHERO_H

#include "Hero.h"

class MedicHero: public Hero
{
private:
    int healingAmt;
public:
    MedicHero();
    MedicHero(double xPos, double yPos, double health, Gun *gun, int healingAmt);
    virtual ~MedicHero();

    int getHealingAmt() const;
    void setHealingAmt(int healingAmt);

    void useSpecial();
};



#endif //MILESTONE1_TEAM16_MEDICHERO_H
