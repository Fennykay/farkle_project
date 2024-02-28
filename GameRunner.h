#include "Player.h"



#ifndef GAMERUNNER_H
#define GAMERUNNER_H

class GameRunner
{
public:
    int computeScore(std::vector<Dice> dice);
    int getScore(Player player);
    void addScore(int score, Player player);
    void resetScore(Player player);

private:
    Player player;
    bool isWinner(Player player);
};


#endif // GAMERUNNER_H