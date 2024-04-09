#include "Player.h"
#include <string>
#include "Dice.h"
#include <iostream>
#include <vector>

using namespace std;


Player::Player(): score(0), tempScore(0)
{
	name = "Player";
}

Player::Player(std::string name): score(0), tempScore(0) {
    this->name = name;
}

void Player::setName(std::string name) {
    this->name = name;
}
std::string Player::getName() {
    return name;
}


vector<vector<Dice>> Player::getSavedDice() {
    return savedDice;
}

void Player::saveDice(vector<Dice> d) {
    savedDice.push_back(d);
}

void Player::resetSavedDice() {
    savedDice.clear();
}

void Player::displaySavedDice() {
    for (vector<Dice> d : savedDice) {
        for (Dice die : d) {
            std::cout << die.getValue() << " ";
        }
    }
    cout << endl;
}

void Player::addTempScore(int score) {
    tempScore += score;
}

void Player::resetTempScore() {
    tempScore = 0;
}

void Player::combineScores() {
    this->score += tempScore;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int score) {
    this->score = score;
}