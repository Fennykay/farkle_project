#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "Dice.h"
#include "Player.h"
#include "GameRunner.h"

std::vector<Player> initPlayers() {
    int numberOfPlayers;
    std::cout << "How many players are there? ";
    std::cin >> numberOfPlayers;

    if (numberOfPlayers < 2) {
        std::cerr << "Error: At least 2 players are required." << std::endl;
        return {}; // Return an empty vector
    }

    std::vector<Player> players;
    players.reserve(numberOfPlayers); // Reserve memory for players
    for (int i = 0; i < numberOfPlayers; i++) {
        std::string name;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;
        players.emplace_back(name); // Emplace instead of push_back
    }
    return players;
}

// Function to print the values of the dice
void printDice(std::vector<Dice>& dice) {
    for (Dice& d : dice) {
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
        std::string diceChoice;
        int temp;

        printDice(dice);
        std::cout << "Would you like to keep any dice? (y/n): ";
        std::cin >> input;

        if (input == "n") {
            keepPicking = false;
            player.saveDice(diceToKeep);
            break;
        }
        
        try {
            std::cout << "Which dice would you like to keep? (1-6): ";
            std::cin.ignore(); // Ignore the newline character
            std::getline(std::cin, diceChoice);
            std::stringstream ss(diceChoice);

            while (ss >> temp) {

                cout << "temp: " << temp << endl;

                if (temp < 1 || temp > dice.size()) {
                    throw std::out_of_range("Invalid choice. Please try again.");
                }
                else {
                    diceToKeep.push_back(dice[temp - 1]);
                    dice.erase(dice.begin() + temp - 1);
                }
            }
            
            player.saveDice(diceToKeep);
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
            // Clear the input stream to prevent getting stuck in a loop
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return dice;
}

std::vector<Dice> initDice() {
    std::vector<Dice> diceSet(6);
    return diceSet;
}

int main() {
    GameRunner gameRunner;
    std::vector<Dice> diceSet;
    std::string input;
    int playerIterator = 0;

    std::vector<Player> players = initPlayers();
    if (players.empty()) return 1; // Exit if no players

    Player activePlayer = players[playerIterator]; 
    bool play = true;

    while (play) {
        diceSet = initDice();
        // Roll the dice
        for (auto& d : diceSet) {
            d.roll();
        }
        // Pick dice to keep for the player
        pickDiceToKeep(diceSet, activePlayer);

        std::cout << "Do you want to roll again? (y/n): ";
        std::cin >> input;

        if (input == "n") {
            activePlayer.displaySavedDice();
            playerIterator = (playerIterator + 1) % players.size(); // Move to the next player
            activePlayer = players[playerIterator];
            cout << activePlayer.getName() << ", it is your turn" << endl;
        }
    }

    try
    {
        for (auto& player : players) {
            std::cout << player.getName() << " score: " << gameRunner.computeScore(player.getSavedDice()[0]) << std::endl;
            }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}