#include "GameRunner.h"
#include "Player.h"
#include <iostream>
#include <stdlib.h>



int GameRunner::getScore() {
    return score;
}

void GameRunner::addScore(int score) {
    this->score += score;
}

void GameRunner::resetScore() {
    score = 0;
}

void GameRunner::setPlayer(Player player) {
    this->player = player;
}

bool GameRunner::isWinner() {
    return score >= 10000;
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
        score += 50;
    }
    if (counts[4] == 1) {
        score += 50;
    }
    return score;
}
