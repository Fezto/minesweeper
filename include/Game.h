//
// Created by ayrto on 07/06/2025.
//

#ifndef GAME_H
#define GAME_H
#include <string_view>

#include "Board.h"
#include "enums/GameState.h"
#include "InputData.h"

/**
 * @brief Main game controller for the minesweeper application
 *
 * The Game class orchestrates the entire minesweeper game flow, including
 * user interaction, game logic, win/lose condition checking, and display.
 * It acts as the central coordinator between the Board and user interface.
 */
class Game
{
private:
    // * Properties
    Board board;                          ///< The game board containing all cells
    GameState state = GameState::Playing; ///< Current state of the game

public:
    /**
     * @brief Constructs a new Game with specified board dimensions and mine count
     *
     * @param columns Number of columns for the game board
     * @param rows Number of rows for the game board
     * @param mines Number of mines to place on the board
     *
     * @pre columns > 0 && rows > 0 && mines >= 0
     * @pre mines < (columns * rows) to ensure valid mine placement
     */
    Game(int columns, int rows, int mines);

    // * Getters

    /**
     * @brief Checks if the game is currently in progress
     * @return bool True if the game state is Playing
     */
    bool isPlaying() const;

    /**
     * @brief Checks if the player has won the game
     * @return bool True if the game state is Won
     */
    bool isWon() const;

    /**
     * @brief Checks if the player has lost the game
     * @return bool True if the game state is Lost
     */
    bool isLost() const;

    // * Setters

    /**
     * @brief Sets the game state to Won
     *
     * Called when all non-mine cells have been revealed.
     * This will cause the game loop to terminate with a victory message.
     */
    void setWon();

    /**
     * @brief Sets the game state to Lost
     *
     * Called when the player reveals a cell containing a mine.
     * This will cause the game loop to terminate with a defeat message.
     */
    void setLost();

    // * Interaction

    /**
     * @brief Starts and runs the main game loop
     *
     * Handles the complete game flow:
     * - Displays the board
     * - Prompts for user input
     * - Validates and processes moves
     * - Checks win/lose conditions
     * - Continues until game ends
     *
     * @note This method blocks until the game is completed
     */
    void start();

    /**
     * @brief Displays input prompt and gets user move
     *
     * Shows instructions for valid input format and reads a line
     * from standard input. Supports formats like "A5", "A5 R", "B3 F".
     *
     * @return std::string The user's input string
     *
     * @note Static method as it doesn't depend on game state
     */
    static std::string prompt();

    /**
     * @brief Validates if the input string matches the expected format
     *
     * @param input The input string to validate
     * @return bool True if the input matches the regex pattern for valid moves
     *
     * Expected format: [A-Z][1-26]( [FR])?
     * - Column: Single letter A-Z
     * - Row: Number 1-26
     * - Action: Optional F (flag) or R (reveal)
     */
    bool isValidInput(const std::string &input) const;

    /**
     * @brief Parses a valid input string into structured data
     *
     * @param input The validated input string to parse
     * @return InputData Structure containing column, row, and action
     *
     * @pre input must be validated with isValidInput() first
     * @note If no action is specified, defaults to 'R' (reveal)
     */
    InputData parseInput(const std::string &input) const;

    /**
     * @brief Processes a player's move on the board
     *
     * @param column Column index (0-based) where the move is made
     * @param row Row index (0-based) where the move is made
     * @param action Action to perform ('R' for reveal, 'F' for flag)
     *
     * Handles:
     * - Flag toggling for 'F' action
     * - Cell revelation and mine checking for 'R' action
     * - Automatic propagation for empty cells
     *
     * @pre Board coordinates must be valid
     */
    void play(int column, int row, char action);

    /**
     * @brief Reveals a cell and propagates to adjacent empty cells
     *
     * @param column Column index (0-based) of the cell to reveal
     * @param row Row index (0-based) of the cell to reveal
     *
     * If the revealed cell is empty (no nearby mines), automatically
     * reveals all adjacent cells recursively until non-empty cells
     * are reached. This implements the classic minesweeper flood-fill!
     *
     * @note Respects flagged cells (won't reveal them)
     * @pre Board coordinates must be valid
     */
    void revealCellAndPropagate(int column, int row);

    // * Utils

    /**
     * @brief Displays the current board state to the terminal
     *
     * Delegates to the Board's print method to render the current
     * state of all cells with proper formatting and colors.
     */
    void print() const;

    /**
     * @brief Clears the terminal screen
     *
     * Uses platform-specific commands:
     * - Windows: "cls"
     * - Unix/Linux/macOS: "clear"
     *
     * @note Static method as it doesn't depend on game state
     */
    static void clear();

    /**
     * @brief Checks if the player has won and updates game state
     *
     * Counts revealed non-mine cells and compares with the total
     * number of non-mine cells on the board. If all non-mine cells
     * are revealed, sets the game state to Won.
     *
     * @note Called after each successful move to detect victory
     */
    void checkWinCondition();

    // Exposed getters (used by web UI)
    int getColumns() const { return board.getColumns(); }
    int getRows() const { return board.getRows(); }
    int getMinesTotal() const { return board.getMines(); }
    int getFlagsCount() const;
    int getRevealedCount() const;
    int getStateValue() const { return static_cast<int>(state); }
};

#endif // GAME_H