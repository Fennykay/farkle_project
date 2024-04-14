#include "Player.h"



#ifndef GAMERUNNER_H
#define GAMERUNNER_H

class GameRunner
{
public:
    
    int getScore(Player player);
    void addScore(int score, Player player);
    void resetScore(Player player);

    int computeHandScore(const std::vector<std::vector<Dice>>& dice);

    bool isWinner(Player player);

    void displayMenu(Player player);
    void displayRules();
    void displayWinner(Player player);

    void runPlayerTurn(Player& player, std::vector<Dice> dice);

private:
    Player player;
    int computeScore(const std::vector<Dice>& dice);
    
};


#endif // GAMERUNNER_H