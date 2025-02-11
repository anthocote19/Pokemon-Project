#include <stdio.h>
#include "player.h"
#define MAX_SUPEMONS 10

void initialize_player(Player *player) {
    player->supemonCount = 0;
    player->supcoins = 100;
    player->selected_supemon = 0;

    for (int i = 0; i < MAX_ITEMS; i++) {
        player->items[i] = 0;
    }
    printf("=====================================\n");
    printf("| Choisissez votre Supemon de depart |\n");
    printf("=====================================\n");
    printf("| 1. Supmander                      |\n");
    printf("| 2. Supasaur                       |\n");
    printf("| 3. Supirtle                       |\n");
    printf("=====================================\n");
    printf("| Entrez votre choix :              |\n");
    printf("=====================================\n");
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
            printf("Choix invalide. Supmander selectionne par défaut.\n");
            player->supemons[0] = create_supemon("Supmander", 10, 1, 1, 1, 2, 1, "Scratch", "Grawl");
    }
    player->supemonCount = 1;
}

void addSupemonToPlayer(Player *player, Supemon newSupemon) {
    if (player->supemonCount < MAX_SUPEMONS) {
        player->supemons[player->supemonCount] = newSupemon;
        player->supemonCount++;
        printf("%s a ete ajoute a votre equipe !\n", newSupemon.name);
    } else {
        printf("Vous avez atteint la limite de Supemons !\n");
    }
}

void changerSupemon(Player *player) {
    if (player->supemonCount == 0) {
        printf("Vous n'avez pas de Supemons dans votre equipe.\n");
        return;
    }

    printf("Supemons actuels :\n");
    for (int i = 0; i < player->supemonCount; i++) {
        printf("%d. %s (HP: %d/%d)\n", i + 1, player->supemons[i].name, player->supemons[i].hp, player->supemons[i].max_hp);
    }

    int choix;
    printf("Choisissez un Supemon à utiliser (1 - %d) : ", player->supemonCount);
    if (scanf("%d", &choix) != 1 || choix < 1 || choix > player->supemonCount) {
        printf("Choix invalide.\n");
        while (getchar() != '\n');
        return;
    }

    player->selected_supemon = choix - 1;
    printf("Vous avez selectionne %s pour le combat !\n", player->supemons[player->selected_supemon].name);
}

void heal_supemons(Player *player) {
    if (player->supcoins >= 50) {
        player->supcoins -= 50;
        for (int i = 0; i < MAX_SUPEMONS; i++) {
            if (player->supemons[i].hp > 0) {
                player->supemons[i].hp = player->supemons[i].max_hp;
            }
        }
        printf("Tous vos Supemons ont ete soignes! Il vous reste %d Supcoins.\n", player->supcoins);
    } else {
        printf("Vous n'avez pas assez de Supcoins pour soigner vos Supemons. Il vous faut 50 Supcoins.\n");
    }
}
