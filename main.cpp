#include <iostream>
#include <string>
#include <vector>

#include "Dice.h"
#include "Player.h"
#include "GameRunner.h"

// Function to initialize players
std::vector<Player> initPlayers() {
    int numberOfPlayers;

    std::cout << "How many players are there? ";
    std::cin >> numberOfPlayers;

    if (numberOfPlayers < 2) {
        std::cout << "Invalid number of players. Please try again." << std::endl;
        return initPlayers();
    }

    std::vector<Player> players;
    for (int i = 0; i < numberOfPlayers; i++) {
        std::string name;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;
        players.emplace_back(name);
    }
    return players;
}

// Function to print the values of the dice
void printDice(const std::vector<Dice>& dice) {
    for (Dice d : dice) {
        std::cout << d.getValue() << " ";
    }
    std::cout << std::endl;
}

// Function to pick dice to keep
std::vector<Dice>& pickDiceToKeep(std::vector<Dice>& dice, Player& player) {
    bool keepPicking = true;
    std::vector<Dice> diceToKeep;
    std::string input;
    while (keepPicking) {
        int diceChoice;

        printDice(dice);
        std::cout << "Would you like to keep any dice? (y/n):";
        std::cin >> input;

        if (input == "n") {
            keepPicking = false;
            player.saveDice(diceToKeep);
            break;
        }
        
        try {

            std::cout << "Which dice would you like to keep? (1-6): ";
            std::cin >> diceChoice;

            if (diceChoice < 1 || diceChoice > dice.size()) {
                throw std::out_of_range("Invalid choice. Please try again.");

            }
            diceToKeep.push_back(dice[diceChoice - 1]);
            dice.erase(dice.begin() + diceChoice - 1);

            std::cout << "Would you like to keep more dice? (y/n): ";
            std::cin >> input;
            if (input == "n") {
                keepPicking = false;
                player.saveDice(diceToKeep);
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            // Clear the input stream to prevent getting stuck in a loop
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return dice;
}

int main() {
    GameRunner gameRunner;
    bool play = true;
    std::string input;
    std::vector<Dice> diceSet = {Dice(), Dice(), Dice(), Dice(), Dice(), Dice()};

    std::vector<Player> players = initPlayers();

    std::vector<std::vector<Dice>> current_dice_holder;

    while (play) {
        // Roll the dice
        for (Dice& d : diceSet) {
            d.roll();
        }
        // Pick dice to keep for the first player
        diceSet = pickDiceToKeep(diceSet, players[0]);

        std::cout << "Do you want to roll again? (y/n): ";
        std::cin >> input;

        if (input == "n") {
            play = false;
        }

        // Display the saved dice for the first player
        players[0].displaySavedDice();
        current_dice_holder = players[0].getSavedDice();
    }

    std::cout << gameRunner.computeHandScore(current_dice_holder) << std::endl;

    return 0;
}
