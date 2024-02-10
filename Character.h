#ifndef MILESTONE1_TEAM16_CHARACTER_H
#define MILESTONE1_TEAM16_CHARACTER_H

#include "Object.h"

class Character: public Object
{
private:
    int xPos, yPos;
    double health;

public:
    Character();
    Character(char type, int xPos, int yPos, double health);
    virtual ~Character();

    int getXPos() const;
    int getYPos() const;
    double getHealth() const;

    void setXPos(int xPos);
    void setYPos(int yPos);
    void setHealth(double health);
};



#endif //MILESTONE1_TEAM16_CHARACTER_H
