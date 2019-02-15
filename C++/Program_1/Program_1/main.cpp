//
//  main.cpp
//  Program_1
//
//  Created by codeslinger on 1/19/19.
//  Copyright © 2019 codeslinger. All rights reserved.
//

#include <iostream>

using namespace std;

class WeaponBehavior {
public:
    virtual void useWeapon() = 0;
};

class AxeBehavior: public WeaponBehavior {
    void useWeapon(){
        cout << "Axe chop!" << endl;
    }
};

class BowAndArrowBehavior: public WeaponBehavior {
    void useWeapon(){
        cout << "Shoot my Bow!" << endl;
    }
};

class SwordBehavior: public WeaponBehavior {
    void useWeapon(){
        cout << "Sword Slash!" << endl;
    }
};

class KnifeBehavior: public WeaponBehavior {
    void useWeapon(){
        cout << "Knife Stab in the flab!" << endl;
    }
};


//Abstract character class
class Character {
public:
    WeaponBehavior* weapon;
    virtual void fight() = 0;
    void setWeapon (WeaponBehavior* w){
        this->weapon = w;
    }
};

class King : public Character {
public:
    void fight(){
        this->weapon->useWeapon();
    }
};

class Queen : public Character {
    public:
    void fight(){
        this->weapon->useWeapon();
    }
};

class Troll : public Character {
    public:
    void fight(){
        this->weapon->useWeapon();
    }
};

class Knight : public Character {
    public:
    void fight(){
        this->weapon->useWeapon();
    }
};

int main(int argc, const char * argv[]) {
    // Weapons
    KnifeBehavior knife;
    SwordBehavior sword;
    AxeBehavior axe;
    BowAndArrowBehavior bow;
    //Characters
    King king;
    Queen queen;
    Troll troll;
    Knight knight;
  
    //give king the sword
    king.setWeapon(&sword);
    //give queen the bow
    queen.setWeapon(&bow);
    //give troll knife
    troll.setWeapon(&knife);
    //give knight axe
    knight.setWeapon(&axe);
    
    king.fight();
    queen.fight();
    troll.fight();
    knight.fight();
    return 0;
}
