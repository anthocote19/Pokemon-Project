#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"

void battle(Player *player) {
    printf("\nVous vous aventurez dans la nature!\n");
    Supemon wild_supemon = create_supemon("Wild Supémon", 10 + rand() % 6, 1, 1, 2, 1, 2, "Scratch", "Growl");

    printf("Un %s sauvage apparait!\n", wild_supemon.name);

    Supemon *player_supemon = &player->supemons[player->selected_supemon];

    while (player_supemon->hp > 0 && wild_supemon.hp > 0) {
        printf("\nVotre Supémon: %s (HP: %d/%d)\n", player_supemon->name, player_supemon->hp, player_supemon->max_hp);
        printf("Supémon Sauvage: %s (HP: %d/%d)\n", wild_supemon.name, wild_supemon.hp, wild_supemon.max_hp);

        printf("Choisissez une action:\n");
        printf("1. Attaquer\n2. Utiliser un Item\n3. Changer de Supémon\n4. Fuite\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: { // Attack
                printf("Choisissez une attaque:\n");
                printf("1. %s\n2. %s\n", player_supemon->moves[0], player_supemon->moves[1]);
                int move_choice;
                scanf("%d", &move_choice);
                if (move_choice == 1 || move_choice == 2) {
                    int damage = player_supemon->attack * (move_choice == 1 ? 3 : 2) / wild_supemon.defense;
                    wild_supemon.hp -= damage;
                    printf("Votre Supémon utilise %s et inflige %d dégats!\n", player_supemon->moves[move_choice - 1], damage);
                } else {
                    printf("Choix invalide.\n");
                }
                break;
            }
            case 2: { // Use Item
                printf("Choisissez un objet:\n");
                printf("1. Potion (%d available)\n2. Super Potion (%d available)\n", player->items[0], player->items[1]);
                int item_choice;
                scanf("%d", &item_choice);

                if (item_choice == 1 && player->items[0] > 0) {
                    player_supemon->hp += 5;
                    if (player_supemon->hp > player_supemon->max_hp) {
                        player_supemon->hp = player_supemon->max_hp;
                    }
                    player->items[0]--;
                    printf("Vous utilisez une Potion! Les HP de votre Supémon monte à %d/%d.\n", player_supemon->hp, player_supemon->max_hp);
                } else if (item_choice == 2 && player->items[1] > 0) {
                    player_supemon->hp += 10;
                    if (player_supemon->hp > player_supemon->max_hp) {
                        player_supemon->hp = player_supemon->max_hp;
                    }
                    player->items[1]--;
                    printf("Vous utilisez une Super Potion! Les HP de votre Supémon monte à %d/%d.\n", player_supemon->hp, player_supemon->max_hp);
                } else {
                    printf("Choix d'objet invalide ou vous n'avez pas l'objet.\n");
                }
                break;
            }
            case 3: // Change Supémon
                printf("Option non implementé.\n");
                break;
            case 4: // Run
                if (rand() % 2 == 0) {
                    printf("Vous vous enfuyez!\n");
                    return;
                } else {
                    printf("Vous ne reussissez pas a vous enfuir!\n");
                }
                break;
            default:
                printf("Action invalide.\n");
        }

        // Wild Supémon attacks
        if (wild_supemon.hp > 0) {
            int damage = wild_supemon.attack * 2 / player_supemon->defense;
            player_supemon->hp -= damage;
            printf("%s sauvage utilise %s et inflige %d dégats!\n", wild_supemon.name, wild_supemon.moves[0], damage);
        }
    }

    if (player_supemon->hp <= 0) {
        printf("Votre Supémon tombe! Vous perdez la bataille.\n");
    } else {
        printf("Vous battez le %s sauvage!\n", wild_supemon.name);
        int reward = 100 + rand() % 401;
        player->supcoins += reward;
        printf("Vous gagnez %d Supcoins!\n", reward);
    }
}

