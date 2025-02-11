#include <stdlib.h>
#include <time.h>
#include "util.h"

int random_range(int min, int max) {
    srand(time(NULL));
    return min + rand() % (max - min + 1);
}

void printWithBorder(char *message) {
    int len = strlen(message);
    printf("\n");
    for (int i = 0; i < len + 4; i++) printf("-");
    printf("\n| %s |\n", message);
    for (int i = 0; i < len + 4; i++) printf("-");
    printf("\n");
}
