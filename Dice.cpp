#include "Dice.h"
#include <stdlib.h>



Dice::Dice() {
    value = 1;
}

int Dice::roll() {
    value = rand() % 6 + 1;
    return value;
}