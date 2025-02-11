#ifndef SUPEMON_H
#define SUPEMON_H

#define MAX_MOVES 2

typedef struct {
    char name[30];        // Nom du Supémon
    int level;            // Niveau
    int hp;               // HP actuels
    int max_hp;           // HP maximum
    int experience;       // Experience
    int attack;           // Attaque
    int defense;          // Défense
    int evasion;          // Évasion
    int accuracy;         // Précision
    int speed;            // Vitesse
    char moves[MAX_MOVES][20];  // Noms des attaques
} Supemon;

Supemon create_supemon(const char *name, int hp, int attack, int defense, int evasion, int accuracy, int speed, const char *move1, const char *move2);


#endif
