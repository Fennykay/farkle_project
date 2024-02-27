#include "Player.h"



#ifndef GAMERUNNER_H
#define GAMERUNNER_H

class GameRunner
{
public:
    int getScore();
    void addScore(int score);
    void resetScore();
    void setPlayer(Player player);
    int computeScore(std::vector<Dice> dice);
private:
    int score;
    Player player;
    bool isWinner();
};


#endif // GAMERUNNER_H