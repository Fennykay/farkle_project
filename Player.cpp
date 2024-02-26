#include "Player.h"
#include <string>
#include "Dice.h"
#include <iostream>
#include <vector>


Player::Player() {
    name = "Player";
    score = 0;
}
Player::Player(std::string name) {
    this->name = name;
    score = 0;
}

void Player::setName(std::string name) {
    this->name = name;
}
std::string Player::getName() {
    return name;
}

void Player::setScore(int score) {
    this->score = score;
}
int Player::getScore() {
    return score;
}

std::vector<Dice> Player::getSavedDice() {
    return savedDice;
}
std::vector<Dice> Player::rollRemainingDice(std::vector<Dice> dice) {
    std::vector<Dice> remainingDice;
    for (int i = 0; i < dice.size(); i++) {
        dice[i].roll();
        remainingDice.push_back(dice[i]);
    }
    return remainingDice;
}