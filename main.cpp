#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>

#include "Dice.h"
#include "GameRunner.h"
#include "Player.h"


const int SCORE_TO_ENTER = 1000; // Score to enter the game
const int SCORE_TO_WIN = 10000; // Score to win the game

void cheat_add_score(Player& player);
void cheat_enter_game(Player& player);

std::vector<Player> init_players();
std::vector<Dice> init_dice();

void print_dice(std::vector<Dice>& dice);
std::vector<Dice>& pick_dice_to_keep(std::vector<Dice>& dice, Player& player, GameRunner gameRunner);
std::vector<Dice> roll_dice(std::vector<Dice>& dice);

void processPlayerTurn(Player& player, GameRunner& gameRunner);
void cycle_player_turn(std::vector<Player>& players, std::vector<Player>::iterator& activePlayer);
void handle_entry_round(Player& player, GameRunner& gameRunner, std::vector<Dice>& diceSet, bool& playerTurn);
void final_round(std::vector<Player>& players, GameRunner& gameRunner, std::vector<Dice>& diceSet);

static void clear_screen() {system("CLS");}

bool check_for_farkle(Player& player, GameRunner& gameRunner);


int main() {
    GameRunner gameRunner; // Create a game runner object
    std::vector<Dice> diceSet = init_dice(); // Initialize the dice set

    std::vector<Player> players = init_players();
    if (players.empty()) return 1; // Exit if no players
    // Init variables
    bool play = true;
    bool playerTurn = true;
    char input;
    
    auto active_player = players.begin(); // Set the active player to the first player
    gameRunner.displayIntroduction(); // Display the introduction
    // main game loop
    while (play) {
        Player& player = *active_player; // set reference to the active player for data manipulation

        if (player.getPassedEntryScore() == true) { // Check if the player has passed the entry score
            roll_dice(diceSet); // Roll the dice
            gameRunner.displayUserMenu(player); // Display the player's menu

            // Pick dice to keep for the player
            pick_dice_to_keep(diceSet, player, gameRunner);
            
            if (check_for_farkle(player, gameRunner)) { // Check for a farkle each roll and submit
                cycle_player_turn(players, active_player);
                diceSet = init_dice();
                clear_screen();
                continue;
			}

            if (diceSet.size() == 0 && gameRunner.computeHandScore(player.getSavedDice()) > 0) { // Check for hot dice
                std::cout << "Hot Dice! You get to roll all 6 dice again." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep for 2 seconds
                diceSet = init_dice();
                player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
                continue;
            }

            std::cout << "Do you want to roll again? (y/n): ";
            std::cin >> input;
            
            if (input == 'n') {
                // Function to process the player's turn and add scores
                processPlayerTurn(player, gameRunner);
                // Check if the player has reached the winning score
                if (player.getScore() >= SCORE_TO_WIN) {
                    std::cout << "Congratulations " << player.getName() << "!" << std::endl;
                    std::cout << "You have reached the winning score of 10000! We are now headed to the final round." << std::endl;

                    gameRunner.setWinner(player); // sets current player as winner going into last round

                    std::this_thread::sleep_for(chrono::seconds(5));
                    play = false; // break the loop to enter the final round
                    continue;
                }

                // Move to the next player
                cycle_player_turn(players, active_player);

                // Reset the dice set
                diceSet = init_dice();
                clear_screen();
            }

            player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score          
            player.resetSavedDice(); // Clear the saved dice
            
        } 
        else { // Else handles the entry round
            while (playerTurn == true) {
                roll_dice(diceSet);
                handle_entry_round(player, gameRunner, diceSet, playerTurn);
            }

            // Move to the next player
            cycle_player_turn(players, active_player);

            // reinitialize playerturn and dice set
            playerTurn = true;
            diceSet = init_dice();
            roll_dice(diceSet);

            clear_screen();
        }
    }
    
    final_round(players, gameRunner, diceSet);

    std::cout << std::endl << std::endl;
    std::cout << "Final Scores:" << std::endl;
    std::cout << "----------------" << std::endl;

    gameRunner.displayScoreBoard(players);
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

// function to add add score mid game
// This is done by entering the letter 'P' during the dice selection phase
void cheat_add_score(Player& player) {
    player.setScore(9500);
    cout << "Score set to 9500" << endl;
}
// function to enter the game mid game
// This is done by entering the letter 'C' during the dice selection phase
void cheat_enter_game(Player& player) {
    player.reachedEntryScore();
    cout << player.getName() << " entered the game" << endl;
}
// Function to initialize the players
std::vector<Player> init_players() {

    int number_of_players;
    std::unordered_map<std::string, int> playerNames;

    std::cout << "How many players are there? ";
    std::cin >> number_of_players;
    clear_screen();

    while (number_of_players < 2) {
		std::cerr << "Error: At least 2 players are required." << std::endl;
		std::cout << "How many players are there? ";
		std::cin >> number_of_players;
		clear_screen();
	}

    std::vector<Player> players;

    players.reserve(number_of_players); // Reserve memory for players
    for (int i = 0; i < number_of_players; i++) {
        std::string name;

        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;

        while (playerNames.find(name) != playerNames.end()) {
            std::cout << "Error: Player name already exists. Please enter a different name: ";
            std::cin >> name;
        }
        playerNames[name] = 1;

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


        switch (input) {
        case 'n':
            player.saveDice(diceToKeep);
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
// Function to initialize the dice
std::vector<Dice> init_dice() {
    std::vector<Dice> dice_set(6);
    return dice_set;
}
// Function to roll the dice
std::vector<Dice> roll_dice(std::vector<Dice>& dice) {
    for (Dice& d : dice) {
        d.roll();
    }
    return dice;
}
// Function to process the player's turn
void processPlayerTurn(Player& player, GameRunner& gameRunner) {
    player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
    player.displaySavedDice(); // Display the saved dice           
    player.resetSavedDice(); // Clear the saved dice
    player.combineScores(); // Combine the scores
    player.resetTempScore(); // Reset the temporary 
}
// Function to cycle through the players
void cycle_player_turn(std::vector<Player>& players, std::vector<Player>::iterator& activePlayer) {
    activePlayer++; // Move to the next player
    if (activePlayer == players.end()) { // If we have reached the end of the vector
        activePlayer = players.begin(); // Reset the iterator
    }
}
// Function to handle the entry round
void handle_entry_round(Player& player, GameRunner& gameRunner, std::vector<Dice>& diceSet, bool& playerTurn) {
    gameRunner.displayUserMenu(player); // Display the player's menu
    pick_dice_to_keep(diceSet, player, gameRunner); // Pick dice to keep for the player
    // Check for Hot Dice
    if (diceSet.size() == 0 && gameRunner.computeHandScore(player.getSavedDice()) > 0) {
        std::cout << "Hot Dice! You get to roll all 6 dice again." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        diceSet = init_dice();
        player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
        return;
    }
    // Check for a Farkle
    if (check_for_farkle(player, gameRunner)) { // Check for a farkle each roll and submit
        diceSet = init_dice();
        clear_screen();
        playerTurn = false;
        return;
    }
    char input;


    std::cout << "Do you want to roll again? (y/n): ";
    std::cin >> input;
    // Switch statement to handle user input
    switch (input) {
    case 'n': // If the user does not want to roll again
        processPlayerTurn(player, gameRunner);
        playerTurn = false;
        // Check if the player has reached the entry score
        if (player.getScore() >= SCORE_TO_ENTER) {
            player.reachedEntryScore();
            clear_screen();
            std::cout << player.getName() << " has entered the game!" << std::endl;

            player.setScore(0);

            std::this_thread::sleep_for(std::chrono::seconds(2));
            clear_screen();
        }
        else { // If the player has not reached the entry score
            clear_screen();
            std::cout << player.getName() << " has not reached the score threshold." << std::endl;
            player.setScore(0);

            std::this_thread::sleep_for(std::chrono::seconds(2));
            clear_screen();
        }
        break;
    case 'C': // Cheat option to enter the game
        cheat_enter_game(player);
        playerTurn = false;
        break;
    default:
        break;
    }

    player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score          
    player.resetSavedDice(); // Clear the saved dice

    std::this_thread::sleep_for(std::chrono::seconds(1));
    roll_dice(diceSet);
    clear_screen();
}
// Function to handle the final round
void final_round(std::vector<Player>& players, GameRunner& gameRunner, std::vector<Dice>& diceSet)
{
    // Init variables
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
        // Keeping this in the case that a user wins before others enter game
        if (player.getPassedEntryScore() == true) {

            gameRunner.displayUserMenu(player); // Display the player's menu

            pick_dice_to_keep(diceSet, player, gameRunner);
            // Check for Hot Dice
            if (diceSet.size() == 0 && gameRunner.computeHandScore(player.getSavedDice()) > 0) { // Check for hot dice
                std::cout << "Hot Dice! You get to roll all 6 dice again." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2)); // sleep for 2 seconds
                diceSet = init_dice();
                player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
                continue;
            }

            if (check_for_farkle(player, gameRunner)) { // Check for a farkle each roll and submit
                cycle_player_turn(players, active_player);
                diceSet = init_dice();
                clear_screen();

                if (active_player == players.end() - 1) {
                    break;
                }
                else {
                    continue;
                }
            }
            else {

                std::cout << "Do you want to roll again? (y/n): ";
                std::cin >> input;


                if (input == 'n') {
                    // Function to process the player's turn
                    processPlayerTurn(player, gameRunner);
                    // If user passes winning score, set as winner
                    if (player.getScore() > gameRunner.getWinner().getScore()) {
                        gameRunner.setWinner(player);
                    }
                    // Check if we have reached final player
                    if (active_player == players.end() - 1) {
                        play = false;
                    }
                    // Move to the next player
                    cycle_player_turn(players, active_player);

                    // Reset the dice set
                    diceSet = init_dice();
                    clear_screen();
                }
                else {
                    player.addTempScore(gameRunner.computeHandScore(player.getSavedDice())); // Add the score to the temporary score
                    player.resetSavedDice(); // Clear the saved dice
                }
            }
        }
        else {
            // for if user has not entered game but is in final round
            while (playerTurn == true) {
				handle_entry_round(player, gameRunner, diceSet, playerTurn);
			}

			// Move to the next player
			cycle_player_turn(players, active_player);

			// reinitialize playerturn and dice set
			playerTurn = true;
			diceSet = init_dice();
			roll_dice(diceSet);

			clear_screen();
		}
    }

    gameRunner.displayWinner(gameRunner.getWinner());
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
// Function to check for a farkle and reset the player's score if so
bool check_for_farkle(Player& player, GameRunner& gameRunner) {
    if (gameRunner.computeHandScore(player.getSavedDice()) == 0) {

        std::cout << "Farkle! You have rolled a zero score." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        player.resetTempScore();
        player.resetSavedDice();
        
        return true;
    }
    return false;
}
