#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Dice.h"
#include <vector>


class Player {
public:
    Player();  // Constructor
    Player(std::string name);  // Constructor with name

    void setName(std::string name);  // Set the name of the player
    std::string getName();  // Get the name of the player

    std::vector<Dice> getSavedDice();  // Get the saved dice of the player
    void saveDice(Dice dice);  // Save a dice
    void resetSavedDice();  // Reset the saved dice
    void displaySavedDice();  // Display the saved dice

    private:
    std::string name;  // Name of the player
    std::vector<std::vector<Dice>> savedDice;  // Array of saved dice

};


#endif 