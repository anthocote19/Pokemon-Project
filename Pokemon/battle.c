#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "battle.h"

// Fonction pour capturer un Supemon
int tryCapture(int max_hp, int current_hp) {
    if (max_hp <= 0) return 0; // Évite la division par zéro

    int capture_chance = ((max_hp - current_hp) * 100) / max_hp;
    if (capture_chance < 0) capture_chance = 0;
    if (capture_chance > 100) capture_chance = 100;

    return (rand() % 100) < capture_chance;
}

// Fonction pour exécuter un combat
void combat(Player *player, Supemon *enemy) {
    Supemon *player_supemon = &player->supemons[player->selected_supemon];
    enemy->hp = enemy->max_hp;

    while (player_supemon->hp > 0 && enemy->hp > 0) {
        printf("\nVotre Supemon: %s (HP: %d/%d)\n", player_supemon->name, player_supemon->hp, player_supemon->max_hp);
        printf("Supemon Ennemi: %s (HP: %d/%d)\n", enemy->name, enemy->hp, enemy->max_hp);

        printf("Choisissez une action:\n1. Attaquer\n2. Utiliser un Item\n3. Capturer\n4. Changer de Supemon\n5. Fuite\n");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Entrée invalide, réessayez.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: { // Attaque
                printf("Choisissez une attaque:\n1. %s\n2. %s\n", player_supemon->moves[0], player_supemon->moves[1]);
                int move_choice;
                if (scanf("%d", &move_choice) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (move_choice == 1 || move_choice == 2) {
                    int damage = (player_supemon->attack * (move_choice == 1 ? 3 : 2) / enemy->defense) + (rand() % 3);
                    enemy->hp -= damage;
                    if (enemy->hp < 0) enemy->hp = 0;
                    printf("Votre Supemon utilise %s et inflige %d dégâts !\n", player_supemon->moves[move_choice - 1], damage);
                } else {
                    printf("Choix invalide.\n");
                }
                break;
            }
            case 3: { // Capture
                int captureAttempts = 0;
                while (captureAttempts < 3) { // Maximum 3 essais
                    int captured = tryCapture(enemy->max_hp, enemy->hp);
                    if (captured) {
                        addSupemonToPlayer(player, *enemy);
                        printf("Supemon capturé avec succès !\n");
                        return; // Quitte le combat
                    } else {
                        printf("Le Supemon ennemi résiste !\n");
                        captureAttempts++;
                    }
                }
                printf("Le Supemon s'échappe après plusieurs essais !\n");
                break;
            }
            case 5: { // Fuite
                printf("DEBUG: Probabilité de fuite: %d%%\n", player_supemon->speed * 10);
                if (rand() % 100 < (player_supemon->speed * 10)) {
                    printf("Vous vous enfuyez !\n");
                    return;
                } else {
                    printf("Vous ne réussissez pas à fuir !\n");
                }
                break;
            }
        }

        // Vérification si l'ennemi est KO avant qu'il n'attaque
        if (enemy->hp <= 0) {
            printf("Le Supemon ennemi est KO ! Vous gagnez !\n");
            int reward = 100 + rand() % 401;
            player->supcoins += reward;
            printf("Vous gagnez %d Supcoins !\n", reward);
            break;
        }

        // Tour de l'ennemi si toujours en vie
        if (enemy->hp > 0) {
            int damage = (enemy->attack * 2 / player_supemon->defense) + (rand() % 3);
            player_supemon->hp -= damage;
            if (player_supemon->hp < 0) player_supemon->hp = 0;
            printf("%s utilise %s et inflige %d dégâts !\n", enemy->name, enemy->moves[0], damage);

            // 🔥 Vérification immédiate après l'attaque de l'ennemi
            if (player_supemon->hp <= 0) {
                printf("Votre Supemon est KO ! Vous perdez la bataille.\n");

                // Correction : Empêche le Pokémon de disparaître après un combat perdu
                player_supemon->hp = 1; // Le Pokémon survit avec 1 HP
                printf("Votre Supemon est gravement blessé, mais il survit avec 1 HP !\n");

                return; // Quitter le combat immédiatement
            }
        }
    }
}
