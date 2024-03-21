#include "Player.h"



#ifndef GAMERUNNER_H
#define GAMERUNNER_H

class GameRunner
{
public:
    
    int getScore(Player player);
    void addScore(int score, Player player);
    void resetScore(Player player);
    void gamePlayLoop(std::vector<Player>& players, std::vector<Dice>& dice);
    int computeScore(const std::vector<Dice>& dice);
private:
    Player player;
    bool isWinner(Player player);
    int computeHandScore(std::vector<std::vector<Dice>>& dice);
};


#endif // GAMERUNNER_H