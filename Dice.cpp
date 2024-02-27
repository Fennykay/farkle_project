#include "Dice.h"
#include <stdlib.h>
#include <iostream>



Dice::Dice() {
    value = 1;
}

int Dice::roll() {
    value = rand() % 6 + 1;
    return value;
}

int Dice::getValue() {
    return value;
}
