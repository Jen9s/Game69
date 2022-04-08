#pragma once

#include "Solder.h"

void Army::ChangeCounter() {
    while (LevelCounter * 5 <= KillCounter) {
        KillCounter -= LevelCounter * 5;
        LevelCounter++;
        AttackFactor += 0.25;
    }
}

void Hero::ChangeCounter() {
    while (pow(2, LevelCounter) <= KillCounter) {
        KillCounter -= pow(2, LevelCounter);
        LevelCounter++;
        AttackFactor += 0.25;
    }
}

void Hero::Duel(Hero &second) {
    while (armor > 0 && second.armor > 0) {
        armor -= second.damage * second.AttackFactor;
        second.armor -= damage * AttackFactor;
    }

    healthy += armor;
    second.healthy += second.armor;

    while (healthy > 0 && second.healthy > 0) {
        healthy -= second.damage * second.AttackFactor;
        if (healthy <= 0) {
            healthy = 0;
            HeroArmy.Army_ = std::vector<Solder>{};
            return;
        }
        second.healthy -= damage * AttackFactor;
        if (second.healthy <= 0) {
            second.healthy = 0;
            second.HeroArmy.Army_ = std::vector<Solder>{};
            return;
        }
    }
}