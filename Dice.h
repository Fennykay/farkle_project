#include <vector>



#ifndef DICE_H
#define DICE_H

class Dice {
public:
    Dice();  // Constructor
    int roll();  // Roll the dice and return the result
    int getValue();  // Return the current value of the dice

private:
    int value;  // Current value of the dice
};

#endif  // DICE_H
