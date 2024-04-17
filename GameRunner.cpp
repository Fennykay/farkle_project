#include "GameRunner.h"
#include "Player.h"
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <string>



int GameRunner::getScore(Player player) {
    return player.getScore();
}

void GameRunner::addScore(int score, Player player) {
    player.addTempScore(score);
}

void GameRunner::resetScore(Player player) {
    player.setScore(0);
}

void GameRunner::displayMenu(Player player)
{
    int width = 30;
    std::cout << "+---------------------------------+" << std::endl;
    std::cout << "| Name: " << std::setw(width - 5) << std::left << player.getName() << " |" << std::endl;
    std::cout << "| Score: " << std::setw(width - 6) << std::left << player.getScore() << " |" << std::endl;
    std::cout << "+---------------------------------+" << std::endl;

}

void GameRunner::displayIntroduction()
{
    std::cout << "Welcome to Farkle!" << std::endl;
    std::cout << "The rules are simple: roll the dice and try to get the highest score possible." << std::endl;
    std::cout << "Here are the rules:" << std::endl << std::endl;
    displayRules();
}

void GameRunner::displayRules()
{
    // create a file stream object
    std::fstream file(RULES_FILE);
    // string for each line of the file
    std::string line;
    // string for the entire file
    std::string rules;
    // read the file line by line
    while (std::getline(file, line))
    {
        rules += line + "\n";
    }
    std::cout << rules << std::endl;
}

void GameRunner::displayWinner(Player player)
{
    std::cout << "Congratulations " << player.getName() << "!" << std::endl;
	std::cout << "You have won the game with a score of " << player.getScore() << "!" << std::endl;
	std::cout << "Thanks for playing!" << std::endl;
}

void GameRunner::runPlayerTurn(Player& player, std::vector<Dice> dice)
{

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

Player GameRunner::getWinner()
{
    return Winner;
}

void GameRunner::setWinner(Player player)
{
    	Winner = player;
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
