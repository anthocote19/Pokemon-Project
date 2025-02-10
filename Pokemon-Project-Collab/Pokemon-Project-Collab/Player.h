#ifndef PLAYER_H
#define PLAYER_H

#include "supemon.h"

#define MAX_ITEMS 10
#define MAX_SUPS 6

typedef struct {
    char name[50];
    Supemon supemons[MAX_SUPS];
    int selected_supemon;
    int supcoins;
    int items[MAX_ITEMS]; // Array of item quantities
} Player;

void initialize_player(Player *player);
void heal_supemons(Player *player);

#endif

