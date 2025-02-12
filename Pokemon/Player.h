#ifndef PLAYER_H
#define PLAYER_H

#include "supemon.h"

#define MAX_SUPS 10
#define MAX_ITEMS 10

typedef struct {
    char name[50];
    Supemon supemons[MAX_SUPS];
    int selected_supemon;
    int supcoins;
    int items[MAX_ITEMS];
    int supemonCount;
    int num_supemons;
    int level;
} Player;

void initialize_player(Player *player);
void addSupemonToPlayer(Player *player, Supemon enemy);

#endif
