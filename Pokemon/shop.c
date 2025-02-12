#include <stdio.h>
#include "shop.h"

void shop(Player *player) {
    printf("\n+============================================+\n");
    printf("|          Bienvenue au Magasin              |\n");
    printf("+============================================+\n");
    printf("| 1. Acheter une Potion         |  100 Supcoins |\n");
    printf("| 2. Acheter une Super Potion   |  300 Supcoins |\n");
    printf("| 3. Acheter un Bonbon Rare     |  700 Supcoins |\n");
    printf("| 4. Quitter le magasin                         |\n");
    printf("+============================================+\n");
    printf("| Supcoins disponibles : %d\n", player->supcoins);
    printf("+============================================+\n");
    printf("Entrez votre choix : ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (player->supcoins >= 100) {
                player->supcoins -= 100;
                player->items[0]++;  // Potion
                printf("Vous achetez une potion!\n");
            } else {
                printf("Pas assez de Supcoins!\n");
            }
            break;
        case 2:
            if (player->supcoins >= 300) {
                player->supcoins -= 300;
                player->items[1]++;  // Super Potion
                printf("Vous achetez une Super Potion!\n");
            } else {
                printf("Pas assez de Supcoins!\n");
            }
            break;
        case 3:
            if (player->supcoins >= 700) {
                player->supcoins -= 700;
                player->items[2]++;  // Bonbon rare
                printf("Vous achetez un bonbon rare!\n");
            } else {
                printf("Pas assez de Supcoins!\n");
            }
            break;
        case 4:
            printf("Vous quittez le magasin.\n");
            return;
        default:
            printf("Choix invalide. Réessayez.\n");
    }
}

void useItem(Player *player, int itemIndex) {
    if (player->items[itemIndex] > 0) {
        player->items[itemIndex]--;

        if (itemIndex == 2) {
            player->level++;
            printf("Vous utilisez un bonbon rare! Votre niveau augmente a %d!\n", player->level);
        } else {
            printf("Vous utilisez un objet!\n");
        }
    } else {
        printf("Vous ne possedez pas cet objet!\n");
    }
}
