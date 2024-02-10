#ifndef MILESTONE1_TEAM16_TANKMONSTER_H
#define MILESTONE1_TEAM16_TANKMONSTER_H

#include "Monster.h"

class TankMonster: public Monster {
private:
    int shield;
public:
    TankMonster();
    TankMonster(double xPos, double yPos, double health, const string &name, int shield);
    virtual ~TankMonster();

    int getShield() const;
    void setShield(int shield);

};


#endif //MILESTONE1_TEAM16_TANKMONSTER_H
