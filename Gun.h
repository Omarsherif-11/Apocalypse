#ifndef MILESTONE1_TEAM16_GUN_H
#define MILESTONE1_TEAM16_GUN_H

#include "Object.h"

#include <string>
#include <iostream>
using namespace std;
class Hero;
class Gun: public Object
{
private:
    string name;
    int bulletNum;
    int dmg;
    int range;
public:
    Gun();
    Gun(char type, const string &name, int bulletNum, int dmg, int range);
    virtual ~Gun();

    const string &getName() const;
    int getBulletNum() const;
    int getDmg() const;
    int getRange() const;

    void setName(const string &name);
    void setBulletNum(int bulletNum);
    void setDmg(int dmg);
    void setRange(int range);
    friend ostream& operator<<(ostream& os, const Gun& gun);
    virtual void useSpecial(Hero &h1, Object ***map);
};




#endif //MILESTONE1_TEAM16_GUN_H
