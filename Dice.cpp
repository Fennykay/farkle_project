#include "Dice.h"
#include <cstdlib> 
#include <iostream>
#include <ctime> 



Dice::Dice() {
    value = 1;
}

int Dice::roll() {
    srand(time(0)); // Seed the random number generator with the current time
    value = rand() % 6 + 1;
    return value;
}

int Dice::getValue() {
    return value;
}
