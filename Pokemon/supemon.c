#include <stdio.h>
#include <string.h>
#include "supemon.h"

Supemon create_supemon(const char *name, int hp, int attack, int defense, int evasion, int accuracy, int speed, const char *move1, const char *move2) {
    Supemon s;
    strcpy(s.name, name);
    s.hp = s.max_hp = hp;
    s.attack = attack;
    s.defense = defense;
    s.evasion = evasion;
    s.accuracy = accuracy;
    s.speed = speed;
    strcpy(s.moves[0], move1);
    strcpy(s.moves[1], move2);
    return s;
}
