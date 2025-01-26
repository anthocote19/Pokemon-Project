#ifndef SUPEMON_H
#define SUPEMON_H

#define MAX_MOVES 2

typedef struct { 
    char name[30];
    int hp, max_hp;
    int attack, base_attack;
    int defense, base_defense;
    int evasion, base_evasion;
    int accuracy, base_accuracy;
    int speed;
    char moves[MAX_MOVES][20]; // Names of moves
} Supemon;

Supemon create_supemon(const char *name, int hp, int attack, int defense, int evasion, int accuracy, int speed, const char *move1, const char *move2);

#endif
