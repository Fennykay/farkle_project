#include "GameRunner.h"
#include "Player.h"
#include <iostream>
#include <stdlib.h>



int GameRunner::getScore(Player player) {
    return player.getScore();
}

void GameRunner::addScore(int score, Player player) {
    score += score;
}

void GameRunner::resetScore(Player player) {
    player.setScore(0);
}

bool GameRunner::isWinner(Player player) {
    return player.getScore() >= 10000;
}

int GameRunner::computeScore(std::vector<Dice> dice) {
    int score = 0;
    std::vector<int> counts(6, 0);
    for (Dice d : dice) {
        counts[d.getValue() - 1]++;
    }
    for (int i = 0; i < 6; i++) {
        if (counts[i] == 3) {
            if (i == 0) {
                score += 1000;
            } else {
                score += (i + 1) * 100;
            }
            counts[i] = 0;
        }
        if (counts[i] > 3) {
            if (i == 0) {
                score += 1000 * (1 << (counts[i] - 3));
            } else {
                score += (i + 1) * 100 * (1 << (counts[i] - 3));
            }
        }
    }
    if (counts[0] == 1) {
        score += 100;
    }
    if (counts[4] == 1) {
        score += 50;
    }
    return score;
}

void GameRunner::gamePlayLoop(std::vector<Player>& players, std::vector<Dice>& dice) {
    
}

