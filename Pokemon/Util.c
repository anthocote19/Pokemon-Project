
#include <stdlib.h>
#include <time.h>
#include "util.h"

int random_range(int min, int max) {
    srand(time(NULL));
    return min + rand() % (max - min + 1);
}


