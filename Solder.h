#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <vector>
#include <sstream>

class Solder {
public:
    std::string name;
    int healthy;
    int armor;
    int damage;
    double AttackFactor = 1;
    int KillCounter = 0;
    int LevelCounter = 1;

    Solder() : healthy(100), armor(60), damage(20) {}

    Solder(int healthy_, int armor_, int damage_) : healthy(healthy_), armor(armor_), damage(damage_) {}

    Solder(int healthy_, int armor_, int damage_, std::string name_) : healthy(healthy_), armor(armor_),
                                                                       damage(damage_), name(std::move(name_)) {}

    virtual void ChangeCounter() {};
};

class Swordsman : public Solder {
public:
    Swordsman() : Solder() {}
};

class Archer : public Solder {
public:
    Archer() : Solder(80, 20, 60) {}
};

class Rider : public Solder {
public:
    Rider() : Solder(120, 40, 40) {}
};

class Army : public Solder {
public:
    std::vector<Solder> Army_;

    explicit Army(int number) {
        for (int i = 0; i < number; i++) {
            switch (rand() % 3) {
                case 0:{
                    Swordsman tmp;
                    Army_.push_back(tmp);
                    break;
                }
                case 1:{
                    Archer tmp;
                    Army_.push_back(tmp);
                    break;
                }
                case 2:{
                    Rider tmp;
                    Army_.push_back(tmp);
                    break;
                }
            }
        }
    }

    void ChangeCounter();

};

class Hero : public Solder {
public:
    int CastlesCounter = 0;
    Army HeroArmy;

    Hero() : Solder(200, 40, 40), HeroArmy(5) {
        std::cout << "Enter character name : ";
        std::cin >> name;
        std::cout << std::endl;
    }

    void ChangeCounter();

    void Duel(Hero &second);

    Hero(std::string name_) : Solder(200, 40, 40, std::move(name_)), HeroArmy(5) {}
};

class Castle {
public:
    int ValueRebuildingArmy = 2;
    std::string WhoseCastle;
    std::string name;
    Army CastleArmy;

    Castle() : CastleArmy(5) {}

    Castle(int ValueRebuildingArmy_, int CastleArmyCounter_, std::string name_) : CastleArmy(CastleArmyCounter_),
                                                                                  ValueRebuildingArmy(
                                                                                          ValueRebuildingArmy_),
                                                                                  name(std::move(name_)) {
    }
};