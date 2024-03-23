#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "Dice.h"
#include "Player.h"
#include "GameRunner.h"

std::vector<Player> init_players() {
    int number_of_players;
    std::cout << "How many players are there? ";
    std::cin >> number_of_players;

    if (number_of_players < 2) {
        std::cerr << "Error: At least 2 players are required." << std::endl;
        return {}; // Return an empty vector
    }

    std::vector<Player> players;
    players.reserve(number_of_players); // Reserve memory for players
    for (int i = 0; i < number_of_players; i++) {
        std::string name;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;
        players.emplace_back(name); // Emplace instead of push_back
    }
    return players;
}

// Function to print the values of the dice
void print_dice(std::vector<Dice>& dice) {
    for (Dice& d : dice) {
        std::cout << d.getValue() << " ";
    }
    std::cout << std::endl;
}

// Function to pick dice to keep
std::vector<Dice>& pick_dice_to_keep(std::vector<Dice>& dice, Player& player) {

    bool keepPicking = true;
    std::vector<Dice> diceToKeep;
    std::string input;

    while (keepPicking) {
        std::string diceChoice;
        int temp;
        std::vector<int> indicesToKeep;

        print_dice(dice);
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
                    indicesToKeep.push_back(temp - 1);
                }
            }

            // Add the selected dice to diceToKeep and remove them from the dice vector
            for (int index : indicesToKeep) {
                diceToKeep.push_back(dice[index]);
            }
            // Sort indices in descending order to avoid changing indices during removal
            std::sort(indicesToKeep.begin(), indicesToKeep.end(), std::greater<int>());
            // Remove the selected dice from the dice vector
            for (int index : indicesToKeep) {
                dice.erase(dice.begin() + index);
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

std::vector<Dice> init_dice() {
    std::vector<Dice> dice_set(6);
    return dice_set;
}

int main() {
	std::vector<Dice> diceSet;
    std::string input;
    int player_iterator = 0;

    std::vector<Player> players = init_players();
    if (players.empty()) return 1; // Exit if no players

    Player active_player = players[player_iterator]; 
    bool play = true;

    while (play) {
        diceSet = init_dice();
        // Roll the dice
        for (auto& d : diceSet) {
            d.roll();
        }
        // Pick dice to keep for the player
        pick_dice_to_keep(diceSet, active_player);

        std::cout << "Do you want to roll again? (y/n): ";
        std::cin >> input;

        if (input == "n") {
            player_iterator = (player_iterator + 1) % players.size(); // Move to the next player
            active_player = players[player_iterator];
            cout << active_player.getName() << ", it is your turn" << endl;
        }
    }

    try
    {
	    GameRunner game_runner;
	    for (auto& player : players) {
            std::cout << player.getName() << " score: " << game_runner.computeScore(player.getSavedDice()[0]) << std::endl;
            }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}