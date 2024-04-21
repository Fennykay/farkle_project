#include "GameRunner.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <chrono>
#include <thread>



int GameRunner::getScore(Player player) {
    return player.getScore();
}

void GameRunner::addScore(int score, Player player) {
    player.addTempScore(score);
}

void GameRunner::resetScore(Player player) {
    player.setScore(0);
}

void GameRunner::displayUserMenu(Player player)
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
    const int CONSOLE_TEXT_COLOR_GREEN = 2;
    const int CONSOLE_TEXT_COLOR_WHITE = 15;
    // set the console text color to green
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, CONSOLE_TEXT_COLOR_GREEN);
    // create a file stream object
    std::fstream file(RULES_FILE);
    std::string line;

    char c;
    // read the file line by line
    while (std::getline(file, line))
    {
        // print each character with a delay
        for (char c : line) {
			std::cout << c;
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
        std::cout << std::endl;
	}
    std::cout << endl;
    // set the console text color back to white
    SetConsoleTextAttribute(console_color, CONSOLE_TEXT_COLOR_WHITE);
}

void GameRunner::displayWinner(Player player)
{
    std::cout << "Congratulations " << player.getName() << "!" << std::endl;
	std::cout << "You have won the game with a score of " << player.getScore() << "!" << std::endl;
	std::cout << "Thanks for playing!" << std::endl;
}

void GameRunner::displayScore(Player& player)
{
    std::cout << setw(30) << player.getName() << " Score: " << player.getScore() << std::endl;
}

void GameRunner::displayChoicesMenu()
{
    int width = 30;

    std::cout << "+---------------------------------+" << std::endl;
    std::cout << "1. Roll the dice" << std::setw(width - 16) << std::left << " |" << std::endl;
	std::cout << "2. Save dice" << std::setw(width - 12) << std::left << " |" << std::endl;
    std::cout << "3. End turn" << std::setw(width - 11) << std::left << " |" << std::endl;
    std::cout << "4. Quit" << std::setw(width - 7) << std::left << " |" << std::endl;
	std::cout << "Enter your choice: ";
}

void GameRunner::displayScoreBoard(std::vector<Player> players)
{
    std::cout << "Scoreboard:" << std::endl;
    for (Player p : players) {
		std::cout << p.getName() << " - " << p.getScore() << std::endl;
	}
}
// function to pass each vector of dice to score function
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
// Function to check if the dice rolled is a Farkle
bool GameRunner::isFarkle(const std::vector<Dice>& dice)
{
    if (computeScore(dice) == 0) {
        return true;
    }
    else {
		return false;
	}
}
// Function to get the winner of the game
Player GameRunner::getWinner()
{
    return Winner;
}
// Function to set the winner of the game
void GameRunner::setWinner(Player player)
{
    	Winner = player;
}
// function to score a vector of dice according to farkle rules
int GameRunner::computeScore(const std::vector<Dice>& dice) {
    int score = 0;
    std::unordered_map<int, int> diceCount;
    // count the number of each dice value
    for (Dice d : dice) {
		diceCount[d.getValue()]++;
	}
    // check for scoring dice
    for (auto it = diceCount.begin(); it != diceCount.end(); it++) {

		int value = it->first;
		int count = it->second;
        // check for 3 of a kind
        if (count >= 3) {
            // if triplet is 1, score 1000
            if (value == 1) {
				score += 1000;
            }
            // else score 100 times the die value
            else {
				score += value * 100;
			}
			count -= 3;
		}
        // check for 1s and 5s to score
        if (value == 1) {
			score += count * 100;
        }
        else if (value == 5) {
			score += count * 50;
		}
	}

	return score;
}
