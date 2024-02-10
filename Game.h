#ifndef MILESTONE1_TEAM16_GAME_H
#define MILESTONE1_TEAM16_GAME_H

#include "Object.h"
#include "Hero.h"
static int Round = 0;
class Game: public Object
{
private:
    Object ***grid;
    int rows;
    int columns;
    Hero* hero;
public:
    Game();
    Game(int rows, int columns);
    virtual ~Game();
    Object ***getGrid() const;
    int getRows() const;
    int getColumns() const;
    Hero * getHero() const;

    void setGrid(Object ***grid);
    void setRows(int rows);
    void setColumns(int columns);
    void setHero( Hero* hero);

    void GenerateMap();
    void showMap();
    void startGame();
    void FireGun(char direction);
    void useGunSpecial();
    int checkGameOver();
    void updateMap();

    void move(Hero &h1, char direction);
};

#endif //MILESTONE1_TEAM16_GAME_H
