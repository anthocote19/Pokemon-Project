#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "player.h"
#include "battle.h"
#include "util.h"

int experienceRequired(int level) {
    return 500 + (level - 1) * 1000;
}

int roundRandomly(float value) {
    return (rand() % 2) ? ceil(value) : floor(value);
}

void levelUp(Supemon *supemon) {
    supemon->level++;
    printWithBorder("Niveau Up!");

    printf("\n%s passe au niveau %d !\n", supemon->name, supemon->level);

    supemon->max_hp = roundRandomly(supemon->max_hp * 1.3);
    supemon->attack = roundRandomly(supemon->attack * 1.3);
    supemon->defense = roundRandomly(supemon->defense * 1.3);
    supemon->speed = roundRandomly(supemon->speed * 1.3);
    supemon->hp = supemon->max_hp;

    printWithBorder("Nouvelles Stats :");
    printf("   HP: %d | ATK: %d | DEF: %d | SPD: %d\n", supemon->max_hp, supemon->attack, supemon->defense, supemon->speed);
    printf("-------------------------------------------------\n");
}

void gainExperience(Supemon *supemon, int exp) {
    printf("\n%s gagne %d XP !\n", supemon->name, exp);
    supemon->experience += exp;

    while (supemon->experience >= experienceRequired(supemon->level)) {
        supemon->experience -= experienceRequired(supemon->level);
        levelUp(supemon);
    }
}

int tryCapture(int max_hp, int current_hp) {
    if (max_hp <= 0) return 0;
    int capture_chance = ((max_hp - current_hp) * 100) / max_hp;
    capture_chance = capture_chance < 0 ? 0 : capture_chance;
    capture_chance = capture_chance > 100 ? 100 : capture_chance;

    return (rand() % 100) < capture_chance;
}

void combat(Player *player, Supemon *enemy) {
    Supemon *player_supemon = &player->supemons[player->selected_supemon];
    enemy->hp = enemy->max_hp;

    while (player_supemon->hp > 0 && enemy->hp > 0) {
        printWithBorder("Combat en Cours");

        printf("Votre Supemon: %s (HP: %d/%d)\n", player_supemon->name, player_supemon->hp, player_supemon->max_hp);
        printf("Supemon Ennemi: %s (HP: %d/%d)\n", enemy->name, enemy->hp, enemy->max_hp);
        printWithBorder("Choisissez une action:");

        printf("\n1. Attaquer\n2. Utiliser un Item\n3. Capturer\n4. Changer de Supemon\n5. Fuite\n");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("\nEntree invalide, reessayez.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                printf("\nChoisissez une attaque:\n1. %s\n2. %s\n", player_supemon->moves[0], player_supemon->moves[1]);
                int move_choice;
                if (scanf("%d", &move_choice) != 1) {
                    printf("\nEntree invalide.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (move_choice == 1 || move_choice == 2) {
                    int damage = (player_supemon->attack * (move_choice == 1 ? 3 : 2) / enemy->defense) + (rand() % 3);
                    enemy->hp -= damage;
                    if (enemy->hp < 0) enemy->hp = 0;
                    printf("Votre Supemon utilise %s et inflige %d degats !\n", player_supemon->moves[move_choice - 1], damage);
                } else {
                    printf("\nChoix invalide.\n");
                }
                break;
            }
            case 3: {
                int captureAttempts = 0;
                while (captureAttempts < 3) {
                    int captured = tryCapture(enemy->max_hp, enemy->hp);
                    if (captured) {
                        char newName[50];
                        printWithBorder("Capture Reussie!");
                        printf("\nBravo ! Vous avez capture un %s ! Donnez-lui un nom : ", enemy->name);
                        scanf("%49s", newName);

                        Supemon capturedSupemon = *enemy;
                        snprintf(capturedSupemon.name, sizeof(capturedSupemon.name), "%s", newName);

                        addSupemonToPlayer(player, capturedSupemon);
                        printf("%s a ete ajoute a votre equipe !\n", newName);
                        return;
                    } else {
                        printf("Le Supemon ennemi resiste !\n");
                        captureAttempts++;
                    }
                }
                printWithBorder("Capture Echouee!");
                printf("Le Supemon s'echappe apres plusieurs essais !\n");
                break;
            }
            case 4: {
                changerSupemon(player);
                player_supemon = &player->supemons[player->selected_supemon];
                break;
            }
            case 5: {
                printf("\nProbabilite de fuite: %d%%\n", player_supemon->speed * 10);
                if (rand() % 100 < (player_supemon->speed * 10)) {
                    printWithBorder("Fuite Reussie");
                    printf("Vous vous enfuyez avec succes !\n");
                    return;
                } else {
                    printWithBorder("Fuite Echouee");
                    printf("Vous ne reussissez pas a fuir !\n");
                }
                break;
            }
            default:
                printWithBorder("Choix Invalide");
                printf("Choix invalide. Essayez a nouveau.\n");
                break;
        }

        if (enemy->hp <= 0) {
            printWithBorder("Victoire!");
            printf("\nLe Supemon ennemi est KO ! Vous gagnez !\n");
            int reward = 100 + rand() % 401;
            player->supcoins += reward;
            printf("Vous gagnez %d Supcoins !\n", reward);

            int exp_gain = 200 + rand() % 301;
            gainExperience(player_supemon, exp_gain);
            break;
        }

        if (enemy->hp > 0) {
            int damage = (enemy->attack * 2 / player_supemon->defense) + (rand() % 3);
            player_supemon->hp -= damage;
            if (player_supemon->hp < 0) player_supemon->hp = 0;
            printf("%s utilise %s et inflige %d degats !\n", enemy->name, enemy->moves[0], damage);

            if (player_supemon->hp <= 0) {
                printWithBorder("Defaite");
                printf("\nVotre Supemon est KO ! Vous perdez la bataille.\n");

                player_supemon->hp = 1;
                printf("Votre Supemon est gravement blesse, mais il survit avec 1 HP !\n");

                return;
            }
        }
    }
}
