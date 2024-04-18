#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "Dice.h"
#include "Player.h"
#include "GameRunner.h"


const int SCORE_TO_ENTER = 1000; // Score to enter the game
const int SCORE_TO_WIN = 10000; // Score to win the game

void cheat_add_score(Player& player);
void cheat_enter_game(Player& player);
std::vector<Player> init_players();
void print_dice(std::vector<Dice>& dice);
std::vector<Dice>& pick_dice_to_keep(std::vector<Dice>& dice, Player& player, GameRunner gameRunner);
std::vector<Dice> init_dice();
std::vector<Dice> roll_dice(std::vector<Dice>& dice);
void processPlayerTurn(Player& player, GameRunner& gameRunner);
void cycle_player_turn(std::vector<Player>& players, std::vector<Player>::iterator& activePlayer);
void handle_entry_round(Player& player, GameRunner& gameRunner, std::vector<Dice>& diceSet, bool& playerTurn);
void final_round(std::vector<Player>& players, GameRunner& gameRunner, std::vector<Dice>& diceSet);
void clear_screen() {system("CLS");}
bool check_for_farkle(std::vector<Dice>& dice, GameRunner& gameRunner);


int main() {
    GameRunner gameRunner; // Create a game runner object
    std::vector<Dice> diceSet = init_dice(); // Initialize the dice set

    std::vector<Player> players = init_players();
    if (players.empty()) return 1; // Exit if no players

    bool play = true;
    bool playerTurn = true;
    char input;

    auto active_player = players.begin(); // Set the active player to the first player
    gameRunner.displayIntroduction(); // Display the introduction

    while (play) {
        Player& player = *active_player;
        roll_dice(diceSet);

        if (player.getPassedEntryScore() == true) {

            gameRunner.displayMenu(player); // Display the player's menu

            // Pick dice to keep for the player
            pick_dice_to_keep(diceSet, player, gameRunner);

            // TODO: #1 test hot dice functionality
            if (diceSet.size() == 0) {
                std::cout << "Hot Dice! You get to roll all 6 dice again." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                diceSet = init_dice();
                player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
                continue;
            }

            std::cout << "Do you want to roll again? (y/n): ";
            std::cin >> input;

            if (input == 'n') {
                // Function to process the player's turn
                processPlayerTurn(player, gameRunner);

                if (player.getScore() >= SCORE_TO_WIN) {
                    std::cout << "Congratulations " << player.getName() << "!" << std::endl;
                    std::cout << "You have reached the winning score of 10000! We are now headed to the final round." << std::endl;

                    gameRunner.setWinner(player);

                    std::this_thread::sleep_for(chrono::seconds(5));
                    play = false;
                    continue;
                }

                // Move to the next player
                cycle_player_turn(players, active_player);

                // Reset the dice set
                diceSet = init_dice();
                clear_screen();
            }
        } 
        else {
            while (playerTurn == true) {
                handle_entry_round(player, gameRunner, diceSet, playerTurn);
            }

            // Move to the next player
            cycle_player_turn(players, active_player);

            playerTurn = true;
            diceSet = init_dice();
            roll_dice(diceSet);

            clear_screen();
        }
    }

    final_round(players, gameRunner, diceSet);
}


void cheat_add_score(Player& player) {
    player.setScore(9500);
    cout << "Score set to 9500" << endl;
}

void cheat_enter_game(Player& player) {
    player.reachedEntryScore();
    cout << player.getName() << " entered the game" << endl;
}


std::vector<Player> init_players() {

    int number_of_players;

    std::cout << "How many players are there? ";
    std::cin >> number_of_players;
    clear_screen();

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

        Player player(name);
        players.emplace_back(player); // Emplace instead of push_back
        clear_screen();
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
std::vector<Dice>& pick_dice_to_keep(std::vector<Dice>& dice, Player& player, GameRunner gameRunner) {

    bool keepPicking = true;
    std::vector<Dice> diceToKeep;
    char input;

    while (keepPicking) {
        std::string diceChoice;
        int temp;
        std::vector<int> indicesToKeep;

        print_dice(dice);
        std::cout << "Would you like to keep any dice? (y/n): ";
        std::cin >> input;


        //TODO: FIX FARKLE CHECK
        switch (input) {
        case 'n':
            keepPicking = false;
            player.saveDice(diceToKeep);

            if (check_for_farkle(diceToKeep, gameRunner)) {
				player.resetTempScore();
				player.resetSavedDice();
				return dice;
			}

            return dice;
        case 'C':
            cheat_enter_game(player);
            return dice;
        case 'P':
            cheat_add_score(player);
            return dice;
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
            diceToKeep.clear(); // Clear the diceToKeep vector
            clear_screen();

        }
        catch (const std::exception& e) {
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

std::vector<Dice> roll_dice(std::vector<Dice>& dice) {
    for (Dice& d : dice) {
        d.roll();
    }
    return dice;
}

void processPlayerTurn(Player& player, GameRunner& gameRunner) {
    player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
    player.displaySavedDice(); // Display the saved dice           
    player.resetSavedDice(); // Clear the saved dice
    player.combineScores(); // Combine the scores
    player.resetTempScore(); // Reset the temporary 
}

void cycle_player_turn(std::vector<Player>& players, std::vector<Player>::iterator& activePlayer) {
    activePlayer++;
    if (activePlayer == players.end()) {
        activePlayer = players.begin(); // Reset the iterator
    }
}

void handle_entry_round(Player& player, GameRunner& gameRunner, std::vector<Dice>& diceSet, bool& playerTurn) {
    gameRunner.displayMenu(player); // Display the player's menu
    pick_dice_to_keep(diceSet, player, gameRunner); // Pick dice to keep for the player

    if (diceSet.size() == 0) {
        std::cout << "Hot Dice! You get to roll all 6 dice again." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        diceSet = init_dice();
        player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
        return;
    }
    char input;


    std::cout << "Do you want to roll again? (y/n): ";
    std::cin >> input;

    switch (input) {
    case 'n':
        processPlayerTurn(player, gameRunner);
        playerTurn = false;

        if (player.getScore() >= SCORE_TO_ENTER) {
            player.reachedEntryScore();
            clear_screen();
            std::cout << player.getName() << " has entered the game!" << std::endl;

            player.setScore(0);

            std::this_thread::sleep_for(std::chrono::seconds(2));
            clear_screen();
        }
        else {
            clear_screen();
            std::cout << player.getName() << " has not reached the score threshold." << std::endl;
            player.setScore(0);

            std::this_thread::sleep_for(std::chrono::seconds(2));
            clear_screen();
        }
        break;
    case 'C':
        cheat_enter_game(player);
        playerTurn = false;
        break;
    default:
        break;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    roll_dice(diceSet);
    clear_screen();
}

void final_round(std::vector<Player>& players, GameRunner& gameRunner, std::vector<Dice>& diceSet)
{
    bool play = true;
    bool playerTurn = true;
    char input;

    diceSet = init_dice(); // Reset the dice set

    auto active_player = players.begin(); // Set the active player to the first player

    while (play) {

        Player& player = *active_player;
        // SKIP CURRENT WINNER TURN
        if (gameRunner.getWinner().getName().compare(player.getName()) == 0) {
            cycle_player_turn(players, active_player);
            continue;
        }

        roll_dice(diceSet);

        if (player.getPassedEntryScore() == true) {

            gameRunner.displayMenu(player); // Display the player's menu

            // Pick dice to keep for the player
            pick_dice_to_keep(diceSet, player, gameRunner);

            std::cout << "Do you want to roll again? (y/n): ";
            std::cin >> input;

            if (input == 'n') {
                // Function to process the player's turn
                processPlayerTurn(player, gameRunner);

                if (player.getScore() > gameRunner.getWinner().getScore()) {
					gameRunner.setWinner(player);
				}

                if (active_player == players.end() - 1) {
					play = false;
                }
                // Move to the next player
                cycle_player_turn(players, active_player);

                // Reset the dice set
                diceSet = init_dice();
                clear_screen();
            }

        }
    }

    gameRunner.displayWinner(gameRunner.getWinner());
}

bool check_for_farkle(std::vector<Dice>& dice, GameRunner& gameRunner)
{
    if (gameRunner.isFarkle(dice)) {
		std::cout << "Farkle! You lose all points for this round." << std::endl;
		return true;
	}
	return false;
}
