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
    vector<Dice> diceToKeep;
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
        diceToKeep.push_back(dice[diceChoice - 1]);
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
    std::vector<Dice> diceSet = {Dice(), Dice(), Dice(), Dice(), Dice(), Dice()};

    std::vector<Player> players = initPlayers();

    while (play) {
        for (Dice& d : diceSet) {
            d.roll();
        }
        diceSet = pickDiceToKeep(diceSet, players[0]);

        std::cout << "Do you want to roll again? (y/n): ";
        std::cin >> input;

        if (input == "n") {
            play = false;
        }

        for (vector<Dice> d : players[0].getSavedDice()) {
            for (Dice die : d) {
                std::cout << die.getValue() << " ";
            }
        }

        for (vector<Dice> d : players[0].getSavedDice()) {
            gameRunner.addScore(gameRunner.computeScore(d));
            cout << 
        }
    }
    return 0;
}
