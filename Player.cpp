#include "Player.h"
#include <string>
#include "Dice.h"
#include <iostream>
#include <vector>


Player::Player() {
    name = "Player";
}
Player::Player(std::string name) {
    this->name = name;
}

void Player::setName(std::string name) {
    this->name = name;
}
std::string Player::getName() {
    return name;
}


std::vector<Dice> Player::getSavedDice() {
    return savedDice;
}

void Player::saveDice(Dice d) {
    savedDice.push_back(d);
}

void Player::resetSavedDice() {
    savedDice.clear();
}

void Player::displaySavedDice() {
    for (Dice d : savedDice) {
        std::cout << d.getValue() << " ";
    }
    std::cout << std::endl;
}