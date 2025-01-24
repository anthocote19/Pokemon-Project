#ifndef FILE_H
#define FILE_H

#include "player.h"

int save_game(const Player *player);
int load_game(Player *player);

#endif
