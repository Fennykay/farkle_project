#include <iostream>
#include <string>
#include <vector>
#include "Dice.h"
#include "Player.h"

int main() {
    bool play = true;
    std::string input;

    Player player1; // Remove parentheses here
    player1.setName("Player 1");
    std::vector<Dice> dice;
    for (int i = 0; i < 6; i++) {
        dice.push_back(Dice());
    }

    while (play) {
        dice = player1.rollRemainingDice(dice);

        for (int i = 0; i < dice.size(); i++) {
            std::cout << "Dice " << i + 1 << ": " << dice[i].roll() << std::endl;
        }

        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> input;
        
        if (input == "n") {
            play = false;
        }
    }
    

    return 0;
}