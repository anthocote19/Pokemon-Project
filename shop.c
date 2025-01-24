#include <stdio.h>
#include "shop.h"

void shop(Player *player) {
    printf("\n Bienvenue dans la magasin!\n");
    printf("1. Acheter une potion (100 Supcoins)\n");
    printf("2. Acheter une super potion (300 Supcoins)\n");
    printf("3. Acheter un bonbon rare (700 Supcoins)\n");
    printf("4. Quitter le magasin\n");
    printf("Entrez votre choix: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (player->supcoins >= 100) {
                player->supcoins -= 100;
                player->items[0]++;
                printf("Vous achetez une potion!\n");
            } else {
                printf("Pas assez de Supcoins!\n");
            }
            break;
        case 2:
            if (player->supcoins >= 300) {
                player->supcoins -= 300;
                player->items[1]++;
                printf("Vous achetez une Super Potion!\n");
            } else {
                printf("Pas assez de Supcoins!\n");
            }
            break;
        case 3:
            if (player->supcoins >= 700) {
                player->supcoins -= 700;
                player->items[2]++;
                printf("Vous achetez un bonbon rare!\n");
            } else {
                printf("Pas assez de Supcoins!\n");
            }
            break;
        case 4:
            printf("Vous quittez le magasin.\n");
            return;
        default:
            printf("Choix invalide. Reessayer.\n");
    }
}

