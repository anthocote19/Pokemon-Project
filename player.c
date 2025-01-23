#include <stdio.h>
#include "player.h"

void initialize_player(Player *player) {
    player->supcoins = 1000;
    player->selected_supemon = 0;

    printf("Choose your starting Supémon:\n");
    printf("1. Supmander\n");
    printf("2. Supasaur\n");
    printf("3. Supirtle\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            player->supemons[0] = create_supemon("Supmander", 10, 1, 1, 1, 2, 1, "Scratch", "Grawl");
            break;
        case 2:
            player->supemons[0] = create_supemon("Supasaur", 9, 1, 1, 3, 2, 2, "Pound", "Foliage");
            break;
        case 3:
            player->supemons[0] = create_supemon("Supirtle", 11, 1, 2, 2, 1, 2, "Pound", "Shell");
            break;
        default:
            printf("Invalid choice. Defaulting to Supmander.\n");
            player->supemons[0] = create_supemon("Supmander", 10, 1, 1, 1, 2, 1, "Scratch", "Grawl");
    }
}

void heal_supemons(Player *player) {
    for (int i = 0; i < MAX_SUPS; i++) {
        if (player->supemons[i].hp > 0) {
            player->supemons[i].hp = player->supemons[i].max_hp;
        }
    }
    printf("All your Supémons have been healed!\n");
}

