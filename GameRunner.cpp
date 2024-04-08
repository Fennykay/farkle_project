#include "GameRunner.h"
#include "Player.h"
#include <iostream>
#include <stdlib.h>
#include <set>



int GameRunner::getScore(Player player) {
    return player.getScore();
}

void GameRunner::addScore(int score, Player player) {
    player.addTempScore(score);
}

void GameRunner::resetScore(Player player) {
    player.setScore(0);
}

bool GameRunner::isWinner(Player player) {
    return player.getScore() >= 10000;
}

int GameRunner::computeHandScore(const std::vector<std::vector<Dice>>& dice)
{
    int scoreHolder = 0;
    for (std::vector<Dice> d : dice)
    {
	    scoreHolder += computeScore(d);
    }
    return scoreHolder;
}

int GameRunner::computeScore(const std::vector<Dice>& dice) {
    int score = 0;
    std::set <int> uniqueDice;
    for (Dice d : dice) {
		uniqueDice.insert(d.getValue());
	}

    for ()
}
