#include "GameRunner.h"
#include "Player.h"
#include <iostream>
#include <unordered_map>
#include <iomanip>



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

void GameRunner::displayMenu(Player player)
{
    int width = 30;
    std::cout << "+---------------------------------+" << std::endl;
    std::cout << "| Name: " << std::setw(width - 5) << std::left << player.getName() << " |" << std::endl;
    std::cout << "| Score: " << std::setw(width - 6) << std::left << player.getScore() << " |" << std::endl;
    std::cout << "+---------------------------------+" << std::endl;

}

int GameRunner::computeHandScore(const std::vector<std::vector<Dice>>& dice)
{
    int scoreHolder = 0;
    for (std::vector<Dice> d : dice)
    {
        if (d.size() == 0)
        {
			continue;
        }
        else {
	    scoreHolder += computeScore(d);
        }
    }

    return scoreHolder;
}

int GameRunner::computeScore(const std::vector<Dice>& dice) {
    int score = 0;
    std::unordered_map<int, int> diceCount;

    for (Dice d : dice) {
		diceCount[d.getValue()]++;
	}

    for (auto it = diceCount.begin(); it != diceCount.end(); it++) {

		int value = it->first;
		int count = it->second;

        if (count >= 3) {
            if (value == 1) {
				score += 1000;
            }
            else {
				score += value * 100;
			}
			count -= 3;
		}

        if (value == 1) {
			score += count * 100;
        }
        else if (value == 5) {
			score += count * 50;
		}
	}

	return score;
}
