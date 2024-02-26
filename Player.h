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

    void setScore(int score);  // Set the score of the player
    int getScore();  // Get the score of the player

    std::vector<Dice> getSavedDice();  // Get the saved dice of the player
    void saveDice(Dice dice);  // Save a dice
    void resetSavedDice();  // Reset the saved dice
    void displaySavedDice();  // Display the saved dice
    std::vector<Dice> rollRemainingDice(std::vector<Dice> dice);  // Roll the remaining dice

    private:
    std::string name;  // Name of the player
    int score;  // Score of the player
    std::vector<Dice> savedDice;  // Array of saved dice

};


#endif 