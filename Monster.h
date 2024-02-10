#ifndef MILESTONE1_TEAM16_MONSTER_H
#define MILESTONE1_TEAM16_MONSTER_H

#include "Character.h"
#include <string>
#include <iostream>
using namespace std;

class Monster: public Character
{
private:
    string name;
public:
    Monster();
    Monster(char type, double xPos, double yPos, double health, const string &name);
    virtual ~Monster();

    const string &getName() const;
    void setName(const string &name);
};



#endif //MILESTONE1_TEAM16_MONSTER_H
