#include "Dice.h"
#include <chrono>
#include <random>




std::mt19937 Dice::rng{static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())};

Dice::Dice() : dist(1, 6) {
    this->value = 1;
}

int Dice::roll() {
    value = dist(rng);
    return value;
}

int Dice::getValue() const {
    return value;
}
