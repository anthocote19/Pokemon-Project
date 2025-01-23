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
    printf("1. Into the Wild (Fight)\n");
    printf("2. Shop\n");
    printf("3. Supémon Center\n");
    printf("4. Save & Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Player player;
    if (load_game(&player)) {
        printf("Game loaded successfully!\n");
    } else {
        printf("Welcome to Supémon! Enter your name: ");
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
                printf("Game saved. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
