#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "Pistol.h"
#include "Bazooka.h"
#include "Rifle.h"
#include "MedicHero.h"
#include "DemolitionHero.h"
#include "GhostMonster.h"
#include "TankMonster.h"
#include "Ammo.h"
#include "Potion.h"
#include "Character.h"
#include "Hero.h"
#include "Gun.h"
#include "Monster.h"
#include "Item.h"
#include "Game.h"
#include <bits/stdc++.h>
static int s = 15;
using namespace std;
mt19937 gen(std::random_device{}());
static Game *game;
static bool valid = true;
int main() {
    game = new Game(15,15);
   game -> startGame();
   Hero * hero = game->getHero();

   while(game->checkGameOver() == -1)
   {
       valid = true;

         cout << "Hero Info:\n" << *hero << endl;

         cout << "Round: " << Round << endl;

         cout << "Enter your action: " << endl;
         cout << " M to Move {W,A,S,D} " << endl;
         cout << " F to Fire {U,L,D,R} " << endl;
         cout << " G for gun special action" << endl;
         cout << " H for Hero special action" << endl;
         cout << " (Controls are case insensitive)" << endl;
         char action;

         cin >> action;

         switch (action)
       {
       case 'M': case 'm':
                char move; cin >> move;
                ::system("cls");

               switch (move) {
                   case 'W': case 'w': game->move(*hero,'W');break;
                   case 'A': case 'a': game->move(*hero,'A');break;
                   case 'S': case 's': game->move(*hero,'S');break;
                   case 'D': case 'd' : game->move(*hero,'D');break;
                   default: cout << "Invalid Move" << endl; valid = false;
               } break;
          case 'F': case 'f':
                    char fire; cin >> fire;
                   ::system("cls");

               switch (fire) {
                    case 'U': case 'u': game->FireGun('U');break;
                    case 'D': case 'd': game->FireGun('D');break;
                    case 'R': case 'r': game->FireGun('R');break;
                    case 'L': case 'l' : game->FireGun('L');break;
                        default: cout << "Invalid Move" << endl; valid = false;
                    } break;

          case 'H': case 'h': ::system("cls"); hero -> useSpecial();break;
          case 'G': case 'g': ::system("cls"); game -> useGunSpecial();break;
        default: ::system("cls"); cout << "Invalid Move" << endl; valid = false;

       }

       if(valid)
            Round++;

       game -> updateMap();

   }
   if(game -> checkGameOver())
       cout << "YOU WIN :) " << endl;
   else
       cout << "GAME OVER :( " << endl;
   delete game;
   return 0;
}

//Object---------------------------------------------------------------------

Object::Object() {
    type = '.';
}

Object::Object(char type) : type(type) {}

Object::~Object()= default;

char Object::getType() const {
    return type;
}

void Object::setType(char type) {
    this -> type = type;
}

std::ostream &operator<<(std::ostream &os, const Object &object) {
    os << "type: " << object.type;
    return os;
}

//Character---------------------------------------------------------------------

Character::Character(): Object('C') {
    this -> xPos = 0;
    this -> yPos = 0;
    this -> health = 100;
}

Character::Character(char type, int xPos, int yPos, double health):
Object(type), xPos(xPos) , yPos(yPos), health(health) {}

Character::~Character() = default;

int Character::getXPos() const {
    return xPos;
}

int Character::getYPos() const {
    return yPos;
}

double Character::getHealth() const {
    return health;
}

void Character::setXPos(int xPos) {
    this -> xPos = xPos;
}

void Character::setYPos(int yPos) {
    this -> yPos = yPos;
}

void Character::setHealth(double health) {
    this -> health = std::max(0.0,health);
}

//Hero---------------------------------------------------------------------

Hero::Hero(Gun *gun) : Character('S', 0, 0, 100), gun(gun) {
    this -> gun = new Gun();
}

Hero::Hero(char type, int xPos, int yPos, double health,Gun *gun):
Character(type,xPos,yPos,health), gun(gun)  {}

Hero::~Hero() = default;

Gun *Hero::getGun() const {
    return gun;
}

void Hero::setGun( Gun *gun) {
    this -> gun = gun;
}

std::ostream &operator<<(std::ostream &os, const Hero &hero) {
    os << "xPos: " << hero.getXPos() << " yPos: " << hero.getYPos() << " Health: " << hero.getHealth() << " \nGun Info:" << *hero.gun;
    return os;
}

Hero* Hero::operator+(const Ammo &ammo) {
    Hero* h= this;
    h->gun->setBulletNum(h->gun->getBulletNum()+ammo.getBulletNum());
    if(dynamic_cast<DemolitionHero*>(h)!= nullptr)
        dynamic_cast<DemolitionHero*>(h)->getGun2()->setBulletNum(dynamic_cast<DemolitionHero*>(h)->getGun2()->getBulletNum()+ammo.getBulletNum());
    return h;
}

Hero* Hero::operator+(const Potion &potion) {
    Hero *h=this;
    h->setHealth(h->getHealth()+potion.getHealAmt());
    return h;
}

Hero *Hero::operator-(Monster *mons) {
    this->setHealth(this->getHealth()-10);

    int dmg = 20;
    int shield ;
    cout << "You Bumped into a monster of health: " << mons->getHealth()<< " hp" << endl;

    if(dynamic_cast<TankMonster*>(mons) != nullptr)
    {
        shield = ((TankMonster *)mons) -> getShield();
        if(shield > 0)
            cout << "WoW! That's a Tank Monster! It has a shield of " << shield << " hp" << endl;
        dmg -= shield;
        ((TankMonster*)mons)->setShield(max(-dmg,0));
        dmg = max(0,dmg);
    }
    mons->setHealth(mons->getHealth()-dmg);

    cout << "Monster may have lost health too! Now: " << mons->getHealth() << " hp"<< endl;

    return this;
}

void Hero::useSpecial() {

}

//Gun---------------------------------------------------------------------

Gun::Gun(): Object('W') {
    this -> name = "Gun";
    this -> bulletNum = 0;
    this -> dmg = 0;
    this -> range = 0;
}

Gun::Gun(char type, const string &name, int bulletNum, int dmg, int range):
Object(type), name(name), bulletNum(bulletNum), dmg(dmg), range(range){}

const string &Gun::getName() const {
    return name;
}

int Gun::getBulletNum() const {
    return bulletNum;
}

int Gun::getDmg() const {
    return dmg;
}

int Gun::getRange() const {
    return range;
}

void Gun::setName(const string &name) {
    this -> name = name;
}

void Gun::setBulletNum(int bulletNum) {
    this -> bulletNum = bulletNum;
}

void Gun::setDmg(int dmg) {
    this -> dmg = dmg;
}

void Gun::setRange(int range) {
    this -> range = range;
}

Gun::~Gun() = default;

ostream& operator<<(ostream& os, const Gun& gun)
{
    os << "\n " << "Name: " << gun.getName()
    << " Bullet Number: " << gun.getBulletNum()
    << " Damage: " << gun.getDmg()
    << " Range: " << gun.getRange();

    return os;
}

void Gun::useSpecial(Hero &h1, Object *** map){//Taking *** to use pointers

}

//Pistol---------------------------------------------------------------------

Pistol::Pistol(): Gun('P', "Pistol", 16, 30, 2) {}

Pistol::Pistol(const string &name):
Gun('P', name, 16, 30, 2){}

Pistol::~Pistol() = default;
void Pistol:: useSpecial(Hero &h1, Object *** map)
{
    cout<< "Pistol special" << endl;

        game -> FireGun('U');
        game -> FireGun('D');
        game -> FireGun('R');
        game -> FireGun('L');

}

//Bazooka---------------------------------------------------------------------

Bazooka::Bazooka(): Gun('B', "Bazooka", 4, 150, 8) {}

Bazooka::Bazooka(const string &name):
Gun('B', name, 4, 150, 8){}

Bazooka::~Bazooka() = default;

void Bazooka:: useSpecial(Hero& h1, Object*** map) {

    int x = h1.getXPos();
    int y = h1.getYPos();

    bool diag1 = x == y;
    bool diag2 = (x + y) == (s - 1);
    if(diag1)
        for( int i = 0 , j = 0 ; i < s ; i++, j++)
            if (dynamic_cast<Monster *>(map[i][j]) != nullptr)
            {
                ( (Monster *) map[i][j])->setHealth(0);
                cout << "You killed a monster!" << endl;
            }

    if(diag2)
        for( int i = s - 1 , j = 0 ; i >= 0 ; i--, j++)
            if (dynamic_cast<Monster *>(map[i][j]) != nullptr)
            {
                ( (Monster *) map[i][j])->setHealth(0);
                cout << "You killed a monster!" << endl;
            }

}




//Rifle---------------------------------------------------------------------

Rifle::Rifle(): Gun('R', "Rifle", 30, 20, 4){}

Rifle::Rifle(const string &name):
Gun('R', name, 30, 20, 4){}

Rifle::~Rifle() = default;

void damageIt(Object *** map, int x, int y, int dmg, int shield)
{
    if (dynamic_cast<Monster *>(map[x][y])) {
        if (dynamic_cast<TankMonster *>(map[x][y]) != nullptr) {
            shield = ((TankMonster *) map[x][y])->getShield();
            if (shield > 0)
                cout << "WoW! That's a Tank Monster! It has a shield of " << shield << " hp" << endl;
            dmg -= shield;
            ((TankMonster *) map[x][y])->setShield(max(-dmg, 0));
            dmg = max(0, dmg);
        }
        ((Monster *) map[x][y])->setHealth(((Monster *) map[x][y])->getHealth() - dmg);

        cout << "You damaged a monster! Their new health is: " << ((Monster *) map[x][y])->getHealth() << " hp"<< endl;

    }
}
void Rifle::useSpecial(Hero &h1, Object ***map) {

        setBulletNum(getBulletNum() - 3);
        int x = h1.getXPos();
        int y = h1.getYPos();
        int r = getRange();
        int shield ;
        int dmg = getDmg();
        while( y++ < s && r--)
            damageIt( map, x, y, dmg, shield);

        y = h1.getYPos();
        r = getRange();
        while( y-- && r-- )
            damageIt( map, x, y, dmg, shield);

        y = h1.getYPos();
        r = getRange();
        while( x-- && r--)
            damageIt( map, x, y, dmg, shield);




}

//Monster---------------------------------------------------------------------

Monster::Monster(): Character('E', 0, 0, 0) {
    this -> name = "Monster";
}

Monster::Monster(char type, double xPos, double yPos, double health, const string &name):
Character(type, xPos, yPos, health){
    this -> name = name;
}

const string &Monster::getName() const {
    return name;
}

void Monster::setName(const string &name) {
    this -> name = name;
}

Monster::~Monster() = default;

//MedicHero---------------------------------------------------------------------

MedicHero::MedicHero(): Hero('M', 0, 0, 100, new Gun()) {
    this -> healingAmt = 0;
}

MedicHero::MedicHero(double xPos, double yPos, double health,  Gun *gun, int healingAmt):
        Hero('M' , xPos, yPos, health, gun), healingAmt(healingAmt) {}

int MedicHero::getHealingAmt() const {
    return healingAmt;
}

void MedicHero::setHealingAmt(int healingAmt) {
    this -> healingAmt = healingAmt;
}

void MedicHero::useSpecial() {
    this -> setHealth(this -> getHealth() + healingAmt);
    if(getHealingAmt() == 0)
        valid = false;
    setHealingAmt(0);

}

MedicHero::~MedicHero() = default;

//DemolitionHero---------------------------------------------------------------------

DemolitionHero::DemolitionHero(): Hero('D', 0, 0, 100, new Gun()) {
    this -> gun2 = new Gun();
}

DemolitionHero::DemolitionHero(double xPos, double yPos, double health,  Gun *gun,  Gun *gun2):
        Hero('D', xPos, yPos, health, gun), gun2(gun2){}

Gun * DemolitionHero::getGun2() const {
    return gun2;
}

void DemolitionHero::setGun2( Gun *gun2) {
    this -> gun2 = gun2;
}

void DemolitionHero::useSpecial() {
    Gun * temp = getGun();
    setGun(getGun2());
    setGun2(temp);
}

DemolitionHero::~DemolitionHero() = default;

//GhostMonster---------------------------------------------------------------------

GhostMonster::GhostMonster(): Monster('G', 0, 0, 100, "GhostMonster") {
    this -> isVisible = false;
}

GhostMonster::GhostMonster(double xPos, double yPos, double health, const string &name, bool isVisible):
Monster('G', xPos, yPos, health, name), isVisible(isVisible){}

bool GhostMonster::getIsVisible() const {
    return isVisible;
}

void GhostMonster::setIsVisible(bool isVisible) {
    this -> isVisible = isVisible;
}

GhostMonster::~GhostMonster() = default;

//TankMonster---------------------------------------------------------------------

TankMonster::TankMonster(): Monster('T', 0, 0, 100, "TankMonster"){
    this -> shield = 20;
}

TankMonster::TankMonster(double xPos, double yPos, double health, const string &name, int shield):
Monster('T', xPos, yPos, health, name), shield(shield){}

int TankMonster::getShield() const {
    return shield;
}

void TankMonster::setShield(int shield) {
    this -> shield = shield;
}

TankMonster::~TankMonster() = default;

//Item---------------------------------------------------------------------

Item::Item(): Object('I') {}

Item::Item(char type) : Object(type) {}

Item::~Item() = default;

//Ammo---------------------------------------------------------------------

Ammo::Ammo(): Item('A') {
    this -> bulletNum = 0;
}

Ammo::Ammo(int bulletNum):
Item('A'), bulletNum(bulletNum){}

int Ammo::getBulletNum() const {
    return bulletNum;
}

void Ammo::setBulletNum(int bulletNum) {
    this -> bulletNum = bulletNum;
}

Ammo::~Ammo() = default;

//Potion---------------------------------------------------------------------

Potion::Potion(): Item('H') {
    this -> healAmt = 0;
}

Potion::Potion(int healAmt):
Item('H'), healAmt(healAmt){}

int Potion::getHealAmt() const {
    return healAmt;
}

void Potion::setHealAmt(int healAmt) {
    this -> healAmt = healAmt;
}

Potion::~Potion() = default;

//Game---------------------------------------------------------------------

Game::Game(): Object('G') {
    this -> rows = 0;
    this -> columns = 0;
    this -> grid = nullptr;
}

Game::Game(int rows, int columns):
Object('X'), rows(rows), columns(columns){
    this -> grid = nullptr;
}

Object ***Game::getGrid() const {
    return grid;
}

int Game::getRows() const {
    return rows;
}

int Game::getColumns() const {
    return columns;
}
 Hero * Game::getHero() const {
    return hero;
}

void Game::setGrid(Object ***grid) {
    this -> grid = grid;
}

void Game::setRows(int rows) {
    this -> rows = rows;
}

void Game::setColumns(int columns) {
    this -> columns = columns;
}

void Game::setHero( Hero * hero) {
    this -> hero = hero;
}


void Game::GenerateMap() {
    grid = new Object **[rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new Object *[columns];
        for( int j=0; j < columns; j++)
            grid[i][j] = new Object();
    }
    delete grid[0][0];
    grid[0][0] = hero;

    // 5 Health Potions
    for (int p = 0; p < 5; p++) {
        int x, y;
        do {

            x = uniform_int_distribution<>(0, rows - 1)(gen);
            y = uniform_int_distribution<>(0, columns - 1 )(gen);

        } while(( x == 0 && y == 0) || grid[x][y] -> getType() != '.');
        delete grid[x][y];
        grid[x][y] = new Potion(uniform_int_distribution<>(10, 50)(gen) );;
    }

    // 10 ammo
    for (int a = 0; a < 10; a++) {
        int x, y;
        do {
            x = uniform_int_distribution<>(0, rows - 1 )(gen);
            y = uniform_int_distribution<>(0, columns - 1 )(gen);

        } while (( x == 0 && y == 0) || grid[x][y] -> getType() != '.');
        delete grid[x][y];
        grid[x][y] = new Ammo(uniform_int_distribution<>(5, 20)(gen));
    }

    // 5 GhostMonsters
    for (int g = 0; g < 5; g++) {
        string name = &"Ghost Monster" [g];
        int x, y;
        do {
            x = uniform_int_distribution<>(0, rows - 1)(gen);
            y = uniform_int_distribution<>(0, columns - 1)(gen);

        } while(( x == 0 && y == 0) || grid[x][y] -> getType() != '.');
        delete grid[x][y];
        grid[x][y] = new GhostMonster(x, y, uniform_int_distribution<>(6, 15)(gen) * 10 , name, true);
    }

    // 5 TankMonsters
    for (int g = 0; g < 5; g++) {
        string name = &"Tank Monster" [g];
        int x, y;
        do {
            x = uniform_int_distribution<>(0, rows - 1)(gen);
            y = uniform_int_distribution<>(0, columns - 1)(gen);
        } while(( x == 0 && y == 0) || grid[x][y] -> getType() != '.');
        delete grid[x][y];
        grid[x][y] = new TankMonster(x, y, uniform_int_distribution<>(6, 15)(gen) * 10, name, 20);

    }


}

void Game::showMap() {
    cout<<"MAP : \n";
    for( int i = 0; i < rows; i++ ) {
        for (int j = 0; j < columns; j++) {
            if(grid[i][j] -> getType() == 'G' && !((GhostMonster*)(grid[i][j])) -> getIsVisible())
                cout << '.' << " ";
            else
                cout << grid[i][j]->getType() << "  ";
        }
        cout << endl;
    }
}

Gun *chooseGun(string weapon)
{
    switch (weapon[0]) {
        case '1': return new Pistol();
        case '2': return new Bazooka();
        case '3': return new Rifle();
    }
    return nullptr;

}
void Game::startGame() {
    string heroC;
    do
    {
        cout << "Which Hero would you like to choose:" << endl;
        cout << "Enter 1 for Demolition Hero" << endl;
        cout << "Enter 2 for Medic Hero" << endl;
        cin >> heroC;
    } while( heroC != "1" && heroC != "2");
    string weapon,weapon2;
    do
    {
        cout << "Which weapon would you like to choose:" << endl;
        cout << "Enter 1 for Pistol" << endl;
        cout << "Enter 2 for Bazooka" << endl;
        cout << "Enter 3 for Rifle" << endl;
        cin >> weapon;
    } while( weapon != "1" && weapon != "2" && weapon != "3");
    if(heroC[0] == '1')
    do
    {
        cout << "Which second weapon would you like to choose:" << endl;
        cout << "Enter 1 for Pistol" << endl;
        cout << "Enter 2 for Bazooka" << endl;
        cout << "Enter 3 for Rifle" << endl;
        cin >> weapon2;
    } while( weapon2 != "1" && weapon2 != "2" && weapon2 != "3");
    Hero* hero;
    switch (heroC[0]) {
        case '1': hero = new DemolitionHero(0, 0, 100, chooseGun(weapon), chooseGun(weapon2)) ;break;
        case '2': hero = new MedicHero(0, 0, 100, chooseGun(weapon), 50) ;break;
    }
    this -> hero = hero;
    GenerateMap();
    showMap();
}

void Game:: move(Hero& h1 , char direction)
{
    int x = h1.getXPos();
    int y = h1.getYPos();
    bool block = false;
    switch (direction) {
    case 'W': case 'w': x--;break;
    case 'S': case 's': x++;break;
    case 'A': case 'a': y--;break;
    case 'D': case 'd': y++;break;
        default: cout << "Invalid Choice" << endl; return;

    }
    if( x >= 0 && x < s && y >= 0 && y < s )
    {
        if(dynamic_cast<Potion*>(grid[x][y]) != nullptr)
        {
            h1 = *(h1 + *(Potion*)(grid[x][y]));
        }
        else if(dynamic_cast<Ammo*>(grid[x][y]) != nullptr)
        {
            h1 = *(h1 + *(Ammo*)(grid[x][y]));
        }
        else if(dynamic_cast<Monster*>(grid[x][y]) != nullptr)
        {
            Monster *m = (Monster*)(grid[x][y]);
            h1 = *(h1 - m);

            if(m->getHealth() > 0)
                block = true;
        }
        if(!block)
        {
            delete grid[x][y];
            grid[x][y] = &h1;
            grid[h1.getXPos()][h1.getYPos()] = new Object();
            h1.setXPos(x);
            h1.setYPos(y);
        }
    }
    else
    {
        cout << "Out of Bounds" << endl;
        valid = false;
    }


}
bool ok(int x, char c)
{
    if(c == 'U' || c == 'L')
        return x >= 0;
    return x < 15;
}
void moves(int &x, char c)
{
    if(c == 'U' || c == 'L')
        x --;
    else
        x ++;
}
void Game::FireGun(char direction) {
    Gun * g = (hero -> getGun());
    if(g -> getBulletNum() == 0)return;
    g -> setBulletNum(g -> getBulletNum() - 1);
    int r = g -> getRange();
    int dmg = g -> getDmg();
    int shield = 0;
    int x = hero -> getXPos();
    int y = hero -> getYPos();
    if(direction == 'R' || direction == 'L'){
        for (int i = y + ((direction == 'R') ? 1 : -1) ; ok(i, direction) && r--; moves(i, direction)) {
            if(grid[x][i] -> getType() == 'G' || grid[x][i] -> getType() == 'T'){
                auto monst = (Monster*)(grid[x][i]);

                if(dynamic_cast<TankMonster*>(grid[x][i]) != nullptr)
                {
                    shield = ((TankMonster *)grid[x][i])-> getShield();
                    if(shield > 0)
                        cout << "WoW! That's a Tank Monster! It has a shield of " << shield << " hp" << endl;
                    dmg -= shield;
                    ((TankMonster *)grid[x][i])->setShield(max(-dmg,0));
                    dmg = max(0,dmg);
                }
                monst ->setHealth(monst -> getHealth() - dmg);
                cout << "You damaged a monster! Their new health is: " << monst -> getHealth() << " hp" << endl;
                break;
            }
        }
    }else {
        for (int i = x + ((direction == 'D') ? 1 : -1) ; ok(i, direction) && r--; moves(i, direction)) {
            if(grid[i][y] -> getType() == 'G' || grid[i][y] -> getType() == 'T'){
                auto monst = (Monster*)(grid[i][y]);

                if(dynamic_cast<TankMonster*>(grid[i][y]) != nullptr)
                {
                    shield = ((TankMonster *)grid[i][y])-> getShield();
                    if(shield > 0)
                        cout << "WoW! That's a Tank Monster! It has a shield of " << shield << " hp" << endl;
                    dmg -= shield;
                    ((TankMonster *)grid[i][y])->setShield(max(-dmg,0));
                    dmg = max(0,dmg);
                }
                monst ->setHealth(monst -> getHealth() - dmg);
                cout << "You damaged a monster! Their new health is: " << monst -> getHealth() << " hp" << endl;
                break;
            }
        }

        }

}

void Game::useGunSpecial() {
    Gun * g = (hero -> getGun());
    bool ICanUse = (g -> getType() == 'P' && g -> getBulletNum() >= 4) ||
            (g -> getType() == 'R' && g -> getBulletNum() >= 3) ||
            (g -> getType() == 'B' && ((hero->getXPos() == hero->getYPos()) || ((hero->getXPos() + hero->getYPos()) == 14)));
    if(ICanUse)
       g -> useSpecial(*hero,grid);
    else
        valid = false;
}

int Game::checkGameOver() {
    if(hero->getHealth() <= 0)return 0;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if(grid[i][j] -> getType() == 'G' || grid[i][j] -> getType() == 'T') return -1;
        }
    }
    return 1;
}
void Game::updateMap(){

    //Remove All Dead Monsters
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            Object * o = grid[i][j];
            if(o -> getType() == 'G' || o -> getType() == 'T'){
                if(((Monster*)o) -> getHealth() > 0)continue;
                delete grid[i][j];
                grid[i][j] = new Object();
            }
        }
    }
    //Hide Ghost Monsters every 3 rounds
    if(Round % 3 == 0 && Round && valid){
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if(grid[i][j] -> getType() == 'G'){
                    ((GhostMonster*)grid[i][j]) -> setIsVisible(!(((GhostMonster*)grid[i][j]) -> getIsVisible()));
                }
            }
        }
    }
    //Every 20 Rounds
    if(Round % 20 == 0 && Round){
        //Randomly Spawn a Ghost Monster
        for (int g = 0; g < 1; g++) {
            string name = &"Ghost Monster" [g];
            int x, y;
            do {
                x = uniform_int_distribution<>(0, rows - 1)(gen);
                y = uniform_int_distribution<>(0, columns - 1)(gen);

            } while(( x == 0 && y == 0) || grid[x][y] -> getType() != '.');
            grid[x][y] = new GhostMonster(x, y, uniform_int_distribution<>(6, 15)(gen) * 10 , name, true);
        }
        //Randomly Spawn a tank monster
        for (int g = 0; g < 1; g++) {
            string name = &"Tank Monster" [g];
            int x, y;
            do {
                x = uniform_int_distribution<>(0, rows - 1)(gen);
                y = uniform_int_distribution<>(0, columns - 1)(gen);
            } while(( x == 0 && y == 0) || grid[x][y] -> getType() != '.');
            grid[x][y] = new TankMonster(x, y, uniform_int_distribution<>(6, 15)(gen) * 10, name, true);
        }
    }
    showMap();

}
Game::~Game() {
    for (int i = 0; i < s; ++i) {
            for (int j = 0; j < rows; ++j) {
                delete grid[i][j];
            }
            delete[] grid[i];
        }

        delete[] grid;
}

















































