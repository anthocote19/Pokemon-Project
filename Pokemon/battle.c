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
    int lower = (int)value;
    float decimal = value - lower;
    if (decimal == 0) return lower;
    return (rand() % 2 == 0) ? lower : (lower + 1);
}

Supemon* choisirSupemon(Player *player);

Supemon* choisirSupemon(Player *player) {
    int choix;

    while (1) {
        printf("\nchoisissez le supemon a envoyer au combat :\n");

        for (int i = 0; i < player->supemonCount; i++) {
            Supemon *s = &player->supemons[i];
            printf("%d. %s (niv %d) - hp: %d/%d\n", i + 1, s->name, s->level, s->hp, s->max_hp);
        }

        printf("\nentrez le numéro de votre supemon : ");
        if (scanf("%d", &choix) != 1) {
            printf("\nentree invalide\n");
            while (getchar() != '\n');
            continue;
        }

        if (choix < 1 || choix > player->supemonCount) {
            printf("\nchoix invalide, essayez encore\n");
            continue;
        }

        Supemon *choisi = &player->supemons[choix - 1];

        if (choisi->hp <= 0) {
            printf("\nce supemon est ko, choisissez-en un autre\n");
            continue;
        }

        printf("\n%s entre en combat\n", choisi->name);
        return choisi;
    }
}

void appliquerEffetMouvement(Supemon *supemon, const char *mouvement) {
    if (strcmp(mouvement, "Grognement") == 0) {
        supemon->attack += 1;  // Augmente l'attaque de 1
        printf("%s utilise Grognement. Son attaque augmente de 1.\n", supemon->name);
    }
    else if (strcmp(mouvement, "Feuillage") == 0) {
        supemon->evasion += 1;  // Augmente l'évasion de 1
        printf("%s utilise Feuillage. Son évasion augmente de 1.\n", supemon->name);
    }
    else if (strcmp(mouvement, "Coquille") == 0) {
        supemon->defense += 1;  // Augmente la défense de 1
        printf("%s utilise Coquille. Sa défense augmente de 1.\n", supemon->name);
    }
    else {
        printf("Mouvement inconnu.\n");
    }
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
    printf("   HP: %d | ATK: %d | DEF: %d | SPD: %d\n",
           supemon->max_hp, supemon->attack, supemon->defense, supemon->speed);
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

void printSupemonStats(const char *name, const char *owner, int hp, int max_hp, int level, int attack, int defense, int accuracy, int evasion) {
    printf("%s (%s)\n", name, owner);
    printf("------------------------------------\n");
    printf("HP: %d/%d       Lvl: %d\n", hp, max_hp, level);
    printf("Atk: %d         Def: %d\n", attack, defense);
    printf("Acc: %d         Eva: %d\n", accuracy, evasion);
    printf("------------------------------------\n");
}

void scaleEnemyStats(Supemon *enemy, int player_level) {
    float scale_factor = 1.0f + (player_level - enemy->level) * 0.1f;

    if (scale_factor < 0.5f) scale_factor = 0.5f;
    if (scale_factor > 2.0f) scale_factor = 2.0f;

    enemy->level = player_level;
    enemy->max_hp = (int)(enemy->max_hp * scale_factor);
    enemy->hp = enemy->max_hp;
    enemy->attack = (int)(enemy->attack * scale_factor);
    enemy->defense = (int)(enemy->defense * scale_factor);
    enemy->accuracy = (int)(enemy->accuracy * scale_factor);
    enemy->evasion = (int)(enemy->evasion * scale_factor);
}


void combat(Player *player, Supemon *enemy) {
    Supemon *player_supemon = choisirSupemon(player);
    scaleEnemyStats(enemy, player_supemon->level);
    enemy->hp = enemy->max_hp;

    while (player_supemon->hp > 0 && enemy->hp > 0) {
        printf("\nVotre tour...\n\n");

        printSupemonStats(enemy->name, "enemy", enemy->hp, enemy->max_hp, enemy->level, enemy->attack, enemy->defense, enemy->accuracy, enemy->evasion);
        printSupemonStats(player_supemon->name, player->name, player_supemon->hp, player_supemon->max_hp, player_supemon->level, player_supemon->attack, player_supemon->defense, player_supemon->accuracy, player_supemon->evasion);

        printf("Choisissez une action :\n");
        printf("1. Attaquer\n2. Utiliser un Item\n3. Capturer\n4. Changer de Supemon\n5. Fuite\n");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("\nEntree invalide, reessayez.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                // Choisir une attaque (de dégâts ou de statut)
                printf("\nChoisissez une attaque:\n1. %s (Dégâts)\n2. %s (Augmenter les stats)\n",
                       player_supemon->moves[0], player_supemon->moves[1]);
                int move_choice;
                if (scanf("%d", &move_choice) != 1) {
                    printf("\nEntrée invalide.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (move_choice == 1) {
                    // Attaque de dégâts
                    int damage = (player_supemon->attack * 3 / enemy->defense) + (rand() % 3);
                    enemy->hp -= damage;
                    if (enemy->hp < 0) enemy->hp = 0;
                    printf("\n%s utilise %s et inflige %d dégâts !\n",
                           player_supemon->name, player_supemon->moves[0], damage);
                }
                else if (move_choice == 2) {
                    // Attaque qui augmente les stats
                    if (strcmp(player_supemon->moves[1], "Grognement") == 0) {
                        // Augmenter l'attaque
                        player_supemon->attack += 1;
                        printf("%s utilise Grognement. Son attaque augmente de 1.\n", player_supemon->name);
                    }
                    else if (strcmp(player_supemon->moves[1], "Feuillage") == 0) {
                        // Augmenter l'évasion
                        player_supemon->evasion += 1;
                        printf("%s utilise Feuillage. Son évasion augmente de 1.\n", player_supemon->name);
                    }
                    else if (strcmp(player_supemon->moves[1], "Coquille") == 0) {
                        // Augmenter la défense
                        player_supemon->defense += 1;
                        printf("%s utilise Coquille. Sa défense augmente de 1.\n", player_supemon->name);
                    }
                    else {
                        printf("\nAttaque inconnue.\n");
                    }
                }
                else {
                    printf("\nChoix invalide.\n");
                }
                break;
            }

            case 2: {
                printf("\nInventaire des objets :\n");
                printf("1. Potion (%d restants)\n", player->items[0]);
                printf("2. Super Potion (%d restants)\n", player->items[1]);
                printf("3. Bonbon Rare (%d restants)\n", player->items[2]);
                printf("4. Retour\n");

                int item_choice;
                if (scanf("%d", &item_choice) != 1) {
                    printf("\nEntrée invalide.\n");
                    while (getchar() != '\n');
                    continue;
                }

                switch (item_choice) {
                    case 1:
                        if (player->items[0] > 0) {
                            player->items[0]--;
                            player_supemon->hp += 20;
                            if (player_supemon->hp > player_supemon->max_hp)
                                player_supemon->hp = player_supemon->max_hp;
                            printf("\nVous utilisez une potion. +20 HP !\n");
                        } else {
                            printf("\nVous n'avez plus de potions !\n");
                        }
                        break;

                    case 2:
                        if (player->items[1] > 0) {
                            player->items[1]--;
                            player_supemon->hp += 50;
                            if (player_supemon->hp > player_supemon->max_hp)
                                player_supemon->hp = player_supemon->max_hp;
                            printf("\nVous utilisez une super potion. +50 HP !\n");
                        } else {
                            printf("\nVous n'avez plus de super potions !\n");
                        }
                        break;

                    case 3:
                        if (player->items[2] > 0) {
                            player->items[2]--;
                            player_supemon->level++;
                            printf("\nVous utilisez un bonbon rare ! %s passe au niveau %d !\n",
                                   player_supemon->name, player_supemon->level);

                            continue;
                        } else {
                            printf("\nVous n'avez plus de bonbons rares !\n");
                        }
                        break;


                    case 4:
                        printf("\nVous décidez de ne pas utiliser d'objet.\n");
                        continue;

                    default:
                        printf("\nChoix invalide.\n");
                        break;
                }
                break;
            }

            case 3: {
                int captureAttempts = 0;
                while (captureAttempts < 3) {
                    int captured = tryCapture(enemy->max_hp, enemy->hp);
                    if (captured) {
                        char newName[50];
                        printf("\nCapture Reussie !\n");
                        printf("Bravo ! Vous avez capture un %s ! Donnez-lui un nom : ", enemy->name);
                        scanf("%49s", newName);

                        Supemon capturedSupemon = *enemy;
                        snprintf(capturedSupemon.name, sizeof(capturedSupemon.name), "%s", newName);

                        addSupemonToPlayer(player, capturedSupemon);
                        printf("\n%s a ete ajoute a votre equipe !\n", newName);
                        return;
                    } else {
                        printf("\nLe Supemon ennemi resiste !\n");
                        captureAttempts++;
                    }
                }
                printf("\nCapture Echouee !\nLe Supemon s echappe...\n");
                break;
            }
            case 4: {
                changerSupemon(player);
                player_supemon = &player->supemons[player->selected_supemon];
                break;
            }
            case 5: {
                printf("\nProbabilite de fuite : %d%%\n", player_supemon->speed * 10);
                if (rand() % 100 < (player_supemon->speed * 10)) {
                    printf("\nFuite Reussie ! Vous vous enfuyez avec succes.\n");
                    return;
                } else {
                    printf("\nFuite Echouee ! Vous devez continuer le combat.\n");
                }
                break;
            }
            default:
                printf("\nChoix invalide. Essayez a nouveau.\n");
                break;
        }

        if (enemy->hp <= 0) {
            printf("\nVictoire !\n");
            printf("Le Supemon ennemi est KO ! Vous gagnez !\n");
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
            printf("\n%s utilise %s et inflige %d degats !\n", enemy->name, enemy->moves[0], damage);

            if (player_supemon->hp <= 0) {
                printf("\nDefaite...\n");
                printf("Votre Supemon est KO ! Vous perdez la bataille.\n");

                player_supemon->hp = 1;
                printf("Votre Supemon survit avec 1 HP !\n");

                return;
            }
        }
    }
}

