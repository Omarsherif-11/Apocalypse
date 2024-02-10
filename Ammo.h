#ifndef MILESTONE1_TEAM16_AMMO_H
#define MILESTONE1_TEAM16_AMMO_H

#include "Item.h"

class Ammo: public Item
{
private:
    int bulletNum;
public:
    Ammo();
    Ammo(int bulletNum);
    virtual ~Ammo();

    int getBulletNum() const;
    void setBulletNum(int bulletNum);
};


#endif //MILESTONE1_TEAM16_AMMO_H
