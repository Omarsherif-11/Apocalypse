#ifndef MILESTONE1_TEAM16_ITEM_H
#define MILESTONE1_TEAM16_ITEM_H

#include "Object.h"

class Item: public Object
{
public:
    Item();
    Item(char type);
    virtual ~Item();
};


#endif //MILESTONE1_TEAM16_ITEM_H
