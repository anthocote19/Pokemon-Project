#include <stdlib.h>
#include <time.h>

int tryCapture(int max_hp, int current_hp) {
    if (max_hp <= 0) return 0; // Évite la division par zéro

    int capture_chance = ((max_hp - current_hp) * 100) / max_hp; // Calcul du taux de capture

    // S'assurer que capture_chance reste entre 0 et 100
    if (capture_chance < 0) capture_chance = 0;
    if (capture_chance > 100) capture_chance = 100;

    return (rand() % 100) < capture_chance; // Succès si le nombre aléatoire est inférieur au taux de capture
}
