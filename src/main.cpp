/**
 * @file main.cpp
 * @brief Main entry point for the Minesweeper game application
 * @author ayrto
 * @date 07/06/2025
 */

#include <iostream>
#include <string>
#include <regex>

#include "Message.h"
#include "Game.h"

/**
 * @brief Main function - handles user input for board dimensions and starts the game
 * @return 0 on success, 1 on error
 */
int main() {
    // Welcome message and input prompt
    std::cout << "Welcome to Minesweeper <3\n";
    std::cout << "Select your board dimensions (e.g. 8x10):\n\n";

    std::string boardSize{};

    // Regex pattern for board size validation (format: NxN or NXN)
    std::regex boardSizeValidation{"^[0-9]+[xX][0-9]+$"};

    // Input validation loop
    while (true) {
        std::cout << "-> ";
        std::getline(std::cin, boardSize);
        if (std::regex_match(boardSize, boardSizeValidation))
            break;
        Message::warn("Invalid format. Use 'number x number' like '10x8'");
    }

    // Parse dimensions and create game with error handling
    try {
        // Find separator position (case-insensitive)
        size_t xPos = boardSize.find('x');
        if (xPos == std::string::npos) {
            xPos = boardSize.find('X');
        }

        // Parse columns and rows from input string
        int columns{std::stoi(boardSize.substr(0, xPos))};
        int rows{std::stoi(boardSize.substr(xPos + 1))};

        // Validate board dimensions (5x5 to 15x15)
        if (columns < 5 || rows < 5 || columns > 15 || rows > 15) {
            Message::warn("Dimensions must be between 5x5 and 15x15");
            return 1;
        }

        // Calculate mine count (12.5% density for balanced gameplay)
        int mines = std::max(1, (columns * rows) / 8);
        Game minesweeper = Game(columns, rows, mines);
        minesweeper.start();
    } catch (const std::invalid_argument &e) {
        Message::warn("Error: Invalid numbers in dimensions");
        return 1;
    } catch (const std::exception &e) {
        Message::warn("Unexpected error: " + std::string(e.what()));
        return 1;
    }

    return 0;
}
