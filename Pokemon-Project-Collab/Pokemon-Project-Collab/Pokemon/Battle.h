#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"

// Fonction pour exécuter un combat
void combat(Player *player, Supemon *enemy);
// Fonction pour capturer un Supemon
int tryCapture(int max_hp, int current_hp);

#endif // BATTLE_H
