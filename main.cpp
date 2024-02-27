#include <iostream>
#include <string>
#include <vector>
#include "Dice.h"
#include "Player.h"
#include "GameRunner.h"

std::vector<Player> initPlayers() {
    int numberOfPlayers;

    std::cout << "How many players are there? ";
    std::cin >> numberOfPlayers;

    std::vector<Player> players;
    for (int i = 0; i < numberOfPlayers; i++) {
        std::string name;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;
        players.push_back(Player(name));
    }
    return players;
}

void printDice(std::vector<Dice>& dice) {
    for (Dice d : dice) {
        std::cout << d.getValue() << " ";
    }
    std::cout << std::endl;
}

std::vector<Dice>& pickDiceToKeep(std::vector<Dice>& dice, Player& player) {
    bool keepPicking = true;
    std::string input;
    while (keepPicking) {
        int diceChoice;

        printDice(dice);
        std::cout << "Which dice would you like to keep? (1-6): ";
        std::cin >> diceChoice;
        if (diceChoice < 1 || diceChoice > dice.size()-1) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        } 

        player.saveDice(dice[diceChoice - 1]);
        dice.erase(dice.begin() + diceChoice - 1);
        
        std::cout << "Would you like to keep more dice? (y/n): ";
        std:: cin >> input;
        if (input == "n") {
            keepPicking = false;
        }
    }
    return dice;
}





int main() {
    GameRunner gameRunner;
    bool play = true;
    int diceChoice;
    std::string input;
    std::vector<Dice> dice = {Dice(), Dice(), Dice(), Dice(), Dice(), Dice()};

    std::vector<Player> players = initPlayers();

    while (play) {
        for (Dice& d : dice) {
            d.roll();
        }
        dice = pickDiceToKeep(dice, players[0]);

        std::cout << "Do you want to roll again? (y/n): ";
        std::cin >> input;
        
        if (input == "n") {
            play = false;
        }

        for (Dice& playerDice : players[0].getSavedDice()) {
            std::cout << playerDice.getValue() << " ";
        }

        std::cout << "Score: " << gameRunner.computeScore(players[0].getSavedDice()) << std::endl;
    }
    return 0;
}
