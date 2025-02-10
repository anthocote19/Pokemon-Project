#include <stdio.h>
#include "player.h"

void initialize_player(Player *player) {
    player->supemonCount = 0;
    player->supcoins = 1000;
    player->selected_supemon = 0;

    for (int i = 0; i < MAX_ITEMS; i++) {
        player->items[i] = 0;
    }

    printf("Choisissez votre Supémon de départ:\n");
    printf("1. Supmander\n2. Supasaur\n3. Supirtle\n");
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
            printf("Choix invalide. Supmander sélectionné par défaut.\n");
            player->supemons[0] = create_supemon("Supmander", 10, 1, 1, 1, 2, 1, "Scratch", "Grawl");
    }
    player->supemonCount = 1;
}


void addSupemonToPlayer(Player *player, Supemon enemy) {
    if (player->supemonCount < MAX_SUPS) {
        player->supemons[player->supemonCount] = enemy;
        player->supemonCount++;
        printf("%s a rejoint votre équipe !\n", enemy.name);
    } else {
        printf("Votre équipe est pleine ! Impossible de capturer plus de Supémons.\n");
    }
}


void heal_supemons(Player *player) {
    if (player->supcoins >= 50) {
        player->supcoins -= 50;
        for (int i = 0; i < MAX_SUPS; i++) {
            if (player->supemons[i].hp > 0) {
                player->supemons[i].hp = player->supemons[i].max_hp;
            }
        }
        printf("Tous vos Supemons ont ete soignes! Il vous reste %d Supcoins.\n", player->supcoins);
    } else {
        printf("Vous n'avez pas assez de Supcoins pour soigner vos Supemons. Il vous faut 50 Supcoins.\n");
    }
}


