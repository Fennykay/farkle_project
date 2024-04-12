#include "Player.h"
#include <string>
#include "Dice.h"
#include <iostream>
#include <vector>

using namespace std;


Player::Player(): score(0), tempScore(0), Passed_entry_score(false), name("Player")
{}

Player::Player(std::string name): score(0), tempScore(0), Passed_entry_score(false)
{
    this->name = name;
}

void Player::setName(std::string name) {
    this->name = name;
}
std::string Player::getName() {
    return this->name;
}


vector<vector<Dice>> Player::getSavedDice() {
    return this->savedDice;
}

void Player::saveDice(vector<Dice> d) {
    this->savedDice.push_back(d);
}

void Player::resetSavedDice() {
    this->savedDice.clear();
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
    this->tempScore += score;
}

void Player::resetTempScore() {
    this->tempScore = 0;
}

void Player::combineScores() {
    this->score += tempScore;
}

int Player::getScore() const {
    return this->score;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::reachedEntryScore() {
	this->Passed_entry_score = true;
}

bool Player::getPassedEntryScore()
{
    return this->Passed_entry_score;
}
