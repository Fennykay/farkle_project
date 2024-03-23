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
    int computeHandScore(const std::vector<std::vector<Dice>>& dice);
    bool isWinner(Player player);
private:
    Player player;
    int computeScore(const std::vector<Dice>& dice);
    
};


#endif // GAMERUNNER_H