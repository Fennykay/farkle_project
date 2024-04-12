#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Dice.h"
#include <vector>

using namespace std;


class Player {
public:
    Player();  // Constructor
    Player(std::string name);  // Constructor with name

    void setName(std::string name);  // Set the name of the player
    std::string getName();  // Get the name of the player

    vector<vector<Dice>> getSavedDice();  // Get the saved dice of the player
    void saveDice(vector<Dice> dice);  // Save a dice
    void resetSavedDice();  // Reset the saved dice
    void displaySavedDice();  // Display the saved dice

    void addTempScore(int score);  // Add to the temporary score
    void resetTempScore();  // Reset the temporary score
    void combineScores();  // Combine the temporary score with the score
    int getScore() const;  // Get the score of the player
    void setScore(int score);  // Set the score of the player

    void reachedEntryScore();
    bool getPassedEntryScore();


    private:
    string name;  // Name of the player
    vector<std::vector<Dice>> savedDice;  // Array of saved dice
    int score;
    int tempScore;
    bool Passed_entry_score;
};


#endif 