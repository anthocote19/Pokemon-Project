#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Nécessaire pour PlaySound
#include "player.h"
#include "supemon.h"
#include "battle.h"
#include "shop.h"
#include "file.h"

void display_menu() {
    printf("\n=== Supémon CLI Game ===\n");
    printf("1. Direction la nature (Combattre)\n");
    printf("2. Magasin\n");
    printf("3. Centre Supémon \n");
    printf("4. Sauvegarder et quitter\n");
    printf("Entrez votre choix: ");
}

int main() {
    Player player;
    char loadChoice;

    // Lancement de la musique au début
    const char *music_path = "C:\\Users\\Vidal\\OneDrive\\Bureau\\TP SUPINFO\\1CDEC projet Final\\Pokemon\\pokemon.wav";
    if (!PlaySound(TEXT(music_path), NULL, SND_FILENAME | SND_ASYNC)) {
        printf("Erreur : Impossible de lire le fichier audio.\n");
    }

    printf("Voulez-vous charger la sauvegarde existante ? (o/n) : ");
    scanf(" %c", &loadChoice);

    if (loadChoice == 'o' || loadChoice == 'O') {
        if (load_game(&player)) {
            printf("Jeux charge avec succes!\n");
        } else {
            printf("Aucune sauvegarde trouvée. Creons une nouvelle partie.\n");
            printf("Bienvenue dans Supemon! Entrez votre nom: ");
            scanf("%s", player.name);
            initialize_player(&player);
        }
    } else {
        printf("Creons une nouvelle partie.\n");
        printf("Bienvenue dans Supemon! Entrez votre nom: ");
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
                printf("Jeux sauvegarde. Au revoir!\n");
                PlaySound(NULL, NULL, 0); // Arrête la musique avant de quitter
                return 0;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
    return 0;
}
