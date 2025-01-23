#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"

void battle(Player *player) {
    printf("\nYou are venturing into the wild!\n");
    Supemon wild_supemon = create_supemon("Wild Supémon", 10 + rand() % 6, 1, 1, 2, 1, 2, "Scratch", "Growl");

    printf("A wild %s appears!\n", wild_supemon.name);

    Supemon *player_supemon = &player->supemons[player->selected_supemon];

    while (player_supemon->hp > 0 && wild_supemon.hp > 0) {
        printf("\nYour Supémon: %s (HP: %d/%d)\n", player_supemon->name, player_supemon->hp, player_supemon->max_hp);
        printf("Wild Supémon: %s (HP: %d/%d)\n", wild_supemon.name, wild_supemon.hp, wild_supemon.max_hp);

        printf("Choose an action:\n");
        printf("1. Attack\n2. Use Item\n3. Change Supémon\n4. Run\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Attack
                printf("Choose a move:\n");
                printf("1. %s\n2. %s\n", player_supemon->moves[0], player_supemon->moves[1]);
                int move_choice;
                scanf("%d", &move_choice);
                if (move_choice == 1 || move_choice == 2) {
                    int damage = player_supemon->attack * (move_choice == 1 ? 3 : 2) / wild_supemon.defense;
                    wild_supemon.hp -= damage;
                    printf("Your Supémon used %s and dealt %d damage!\n", player_supemon->moves[move_choice - 1], damage);
                } else {
                    printf("Invalid move choice.\n");
                }
                break;
            }
            case 2: { // Use Item
                printf("Choose an item:\n");
                printf("1. Potion (%d available)\n2. Super Potion (%d available)\n", player->items[0], player->items[1]);
                int item_choice;
                scanf("%d", &item_choice);

                if (item_choice == 1 && player->items[0] > 0) {
                    player_supemon->hp += 5;
                    if (player_supemon->hp > player_supemon->max_hp) {
                        player_supemon->hp = player_supemon->max_hp;
                    }
                    player->items[0]--;
                    printf("You used a Potion! Supémon HP restored to %d/%d.\n", player_supemon->hp, player_supemon->max_hp);
                } else if (item_choice == 2 && player->items[1] > 0) {
                    player_supemon->hp += 10;
                    if (player_supemon->hp > player_supemon->max_hp) {
                        player_supemon->hp = player_supemon->max_hp;
                    }
                    player->items[1]--;
                    printf("You used a Super Potion! Supémon HP restored to %d/%d.\n", player_supemon->hp, player_supemon->max_hp);
                } else {
                    printf("Invalid item choice or no items available.\n");
                }
                break;
            }
            case 3: // Change Supémon
                printf("Feature not yet implemented.\n");
                break;
            case 4: // Run
                if (rand() % 2 == 0) {
                    printf("You successfully ran away!\n");
                    return;
                } else {
                    printf("Failed to run away!\n");
                }
                break;
            default:
                printf("Invalid action.\n");
        }

        // Wild Supémon attacks
        if (wild_supemon.hp > 0) {
            int damage = wild_supemon.attack * 2 / player_supemon->defense;
            player_supemon->hp -= damage;
            printf("Wild %s used %s and dealt %d damage!\n", wild_supemon.name, wild_supemon.moves[0], damage);
        }
    }

    if (player_supemon->hp <= 0) {
        printf("Your Supémon fainted! You lost the battle.\n");
    } else {
        printf("You defeated the wild %s!\n", wild_supemon.name);
        int reward = 100 + rand() % 401;
        player->supcoins += reward;
        printf("You earned %d Supcoins!\n", reward);
    }
}

