#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"

void combat(Player *player, Supemon *enemy);
int tryCapture(int max_hp, int current_hp);

#endif
