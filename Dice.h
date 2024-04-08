#include <random>


#ifndef DICE_H
#define DICE_H

class Dice {
public:
    Dice();  // Constructor
    int roll();  // Roll the dice and return the result
    int getValue() const;  // Return the current value of the dice

private:
    int value;  // Current value of the dice
    static std::mt19937 rng;  // Mersenne Twister 19937 generator
    std::uniform_int_distribution<int> dist;  // Moved dist initialization to the constructor
};

#endif  // DICE_H

