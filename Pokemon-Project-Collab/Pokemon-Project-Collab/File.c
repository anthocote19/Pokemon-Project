#include <stdio.h>
#include <string.h>
#include "file.h"

#define SAVE_FILE "savegame.dat"

int save_game(const Player *player) {
    FILE *file = fopen(SAVE_FILE, "wb");
    if (!file) {
        printf("Erreur: Impossible de charger la sauvegarde.\n");
        return 0;
    }
    fwrite(player, sizeof(Player), 1, file);
    fclose(file);
    return 1;
}

int load_game(Player *player) {
    FILE *file = fopen(SAVE_FILE, "rb");
    if (!file) {
        return 0;
    }
    fread(player, sizeof(Player), 1, file);
    fclose(file);
    return 1;
}

