#include <stdio.h>
#include "player.h"

void initialize_player(Player *player) {
    player->supcoins = 1000;
    player->selected_supemon = 0;

    printf("Choisissez votre premier Supémon:\n");
    printf("1. Supmander\n");
    printf("2. Supasaur\n");
    printf("3. Supirtle\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            player->supemons[0] = create_supemon("Supmander", 10, 1, 1, 1, 2, 1, "Griffe", "Grogne");
            break;
        case 2:
            player->supemons[0] = create_supemon("Supasaur", 9, 1, 1, 3, 2, 2, "Poids", "Feuillage");
            break;
        case 3:
            player->supemons[0] = create_supemon("Supirtle", 11, 1, 2, 2, 1, 2, "Poids", "Coquille");
            break;
        default:
            printf("Choix invalide. Choix par defaut : Supmander.\n");
            player->supemons[0] = create_supemon("Supmander", 10, 1, 1, 1, 2, 1, "Griffe", "Grogne");
    }
}

void heal_supemons(Player *player) {
    for (int i = 0; i < MAX_SUPS; i++) {
        if (player->supemons[i].hp > 0) {
            player->supemons[i].hp = player->supemons[i].max_hp;
        }
    }
    printf("Tout vos Supémons ont été soigné!\n");
}

