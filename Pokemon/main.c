#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "player.h"
#include "supemon.h"
#include "battle.h"
#include "shop.h"
#include "file.h"

void display_menu() {
    printf("=====================================\n");
    printf("|      Supermon CLI Game           |\n");
    printf("=====================================\n");
    printf("| 1. Direction la nature (Combattre)|\n");
    printf("| 2. Magasin                        |\n");
    printf("| 3. Centre Supermon                |\n");
    printf("| 4. Sauvegarder et quitter         |\n");
    printf("=====================================\n");
    printf("| Entrez votre choix :              |\n");
    printf("=====================================\n");
}

void start_battle(Player *player) {
    Supemon enemy = {
        .name = "Wild Supemon",
        .hp = 8,
        .max_hp = 8,
        .attack = 1,
        .defense = 2,
        .speed = 1,
        .moves = {"Charge", "Tackle"}
    };

    combat(player, &enemy);
}

int main() {
    Player player;
    char loadChoice;

    const char *music_path = "C:\\Users\\Vidal\\OneDrive\\Bureau\\TP SUPINFO\\1CDEC projet Final\\Pokemon\\pokemon.wav";
    if (!PlaySound(TEXT(music_path), NULL, SND_FILENAME | SND_ASYNC)) {
        printf("Erreur : Impossible de lire le fichier audio.\n");
    }

    printWithBorder("Voulez-vous charger la sauvegarde existante ? (o/n) : ");
    scanf(" %c", &loadChoice);

    if (loadChoice == 'o' || loadChoice == 'O') {
        if (load_game(&player)) {
            printf("Jeux charge avec succes!\n");
        } else {
            printf("Aucune sauvegarde troueée. Creons une nouvelle partie.\n");
            printWithBorder("Bienvenue dans Supemon! Entrez votre nom: ");
            scanf("%s", player.name);
            initialize_player(&player);
        }
    } else {
        printf("Creons une nouvelle partie.\n");
        printWithBorder("Bienvenue dans Supemon! Entrez votre nom: ");
        scanf("%s", player.name);
        initialize_player(&player);
    }

    int choice;
    while (1) {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                start_battle(&player);
                break;
            case 2:
                shop(&player);
                break;
            case 3:
                heal_supemons(&player);
                break;
            case 4:
                save_game(&player);
                printf("Jeux sauvegarde. Au revoir!\n");
                PlaySound(NULL, NULL, 0);
                return 0;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
    return 0;
}
