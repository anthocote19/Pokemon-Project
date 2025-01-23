#include <stdio.h>
#include "shop.h"

void shop(Player *player) {
    printf("\nWelcome to the Shop!\n");
    printf("1. Buy Potion (100 Supcoins)\n");
    printf("2. Buy Super Potion (300 Supcoins)\n");
    printf("3. Buy Rare Candy (700 Supcoins)\n");
    printf("4. Exit Shop\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            if (player->supcoins >= 100) {
                player->supcoins -= 100;
                player->items[0]++;
                printf("You bought a Potion!\n");
            } else {
                printf("Not enough Supcoins!\n");
            }
            break;
        case 2:
            if (player->supcoins >= 300) {
                player->supcoins -= 300;
                player->items[1]++;
                printf("You bought a Super Potion!\n");
            } else {
                printf("Not enough Supcoins!\n");
            }
            break;
        case 3:
            if (player->supcoins >= 700) {
                player->supcoins -= 700;
                player->items[2]++;
                printf("You bought a Rare Candy!\n");
            } else {
                printf("Not enough Supcoins!\n");
            }
            break;
        case 4:
            printf("Exiting shop.\n");
            return;
        default:
            printf("Invalid choice. Try again.\n");
    }
}

