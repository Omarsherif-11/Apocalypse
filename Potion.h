#ifndef MILESTONE1_TEAM16_POTION_H
#define MILESTONE1_TEAM16_POTION_H

#include "Item.h"

class Potion: public Item {
private:
    int healAmt;
public:
    Potion();
    Potion(int healAmt);
    virtual ~Potion();

    int getHealAmt() const;
    void setHealAmt(int healAmt);

};


#endif //MILESTONE1_TEAM16_POTION_H
