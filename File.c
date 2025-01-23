#include <stdio.h>
#include <string.h>
#include "file.h"

#define SAVE_FILE "savegame.dat"

int save_game(const Player *player) {
    FILE *file = fopen(SAVE_FILE, "wb");
    if (!file) {
        printf("Error: Unable to save the game.\n");
        return 0;
    }
    fwrite(player, sizeof(Player), 1, file);
    fclose(file);
    return 1;
}

int load_game(Player *player) {
    FILE *file = fopen(SAVE_FILE, "rb");
    if (!file) {
        return 0; // No save file found
    }
    fread(player, sizeof(Player), 1, file);
    fclose(file);
    return 1;
}

