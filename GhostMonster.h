#ifndef MILESTONE1_TEAM16_GHOSTMONSTER_H
#define MILESTONE1_TEAM16_GHOSTMONSTER_H

#include "Monster.h"

class GhostMonster: public Monster
{
private:
    bool isVisible;
public:
    GhostMonster();
    GhostMonster(double xPos, double yPos, double health, const string &name, bool isVisible);
    virtual ~GhostMonster();

    bool getIsVisible() const;
    void setIsVisible(bool isVisible);


};



#endif //MILESTONE1_TEAM16_GHOSTMONSTER_H
