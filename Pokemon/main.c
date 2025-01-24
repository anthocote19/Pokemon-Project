#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "supemon.h"
#include "battle.h"
#include "shop.h"
#include "file.h"

void display_menu() {
    printf("\n=== Supémon CLI Game ===\n");
    printf("1. Direction la nature (Combattre)\n");
    printf("2. Magasin\n");
    printf("3. Centre Supémon \n");
    printf("4. Sauvegarder et quitter\n");
    printf("Entrez votre choix: ");
}

int main() {
    Player player;
    if (load_game(&player)) {
        printf("Jeux chargé avec succes!\n");
    } else {
        printf("Bienvenue dans Supémon! Entrez votre nom: ");
        scanf("%s", player.name);
        initialize_player(&player);
    }

    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                battle(&player);
                break;
            case 2:
                shop(&player);
                break;
            case 3:
                heal_supemons(&player);
                break;
            case 4:
                save_game(&player);
                printf("Jeux sauvegardé. Au revoir!\n");
                return 0;
            default:
                printf("Choix invalide. Reessayez.\n");
        }
    }
    return 0;
}
