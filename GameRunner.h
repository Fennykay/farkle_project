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
    bool isFarkle(const std::vector<Dice>& dice);

    Player getWinner();
    void setWinner(Player player);

    void displayUserMenu(Player player);
    void displayIntroduction();
    void displayRules();
    void displayWinner(Player player);
    void displayScore(Player& player);
    void displayChoicesMenu();
    void displayScoreBoard(std::vector<Player> players);

private:
    Player player;
    int computeScore(const std::vector<Dice>& dice);
    Player Winner;
    const string RULES_FILE = "FarkleRules.txt";
    
};


#endif // GAMERUNNER_H