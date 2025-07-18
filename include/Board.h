#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <array>
#include "Cell.h"

/**
 * @brief Manages the minesweeper game board and its operations
 *
 * The Board class is responsible for creating, managing, and displaying
 * the minesweeper game board. It handles mine placement, number calculation,
 * coordinate validation, and terminal rendering.
 */
class Board
{
private:
    // * Properties
    int columns;                          ///< Number of columns in the board
    int rows;                             ///< Number of rows in the board
    int mines;                            ///< Total number of mines on the board
    std::vector<std::vector<Cell>> board; ///< 2D grid of cells representing the board

public:
    /**
     * @brief Constructs a new Board with specified dimensions and mine count
     *
     * Creates a board with the given dimensions, places mines randomly,
     * and calculates the numbers for all non-mine cells.
     *
     * @param columns Number of columns (width) of the board
     * @param rows Number of rows (height) of the board
     * @param mines Number of mines to place on the board
     *
     * @pre columns > 0 && rows > 0 && mines >= 0
     * @pre mines < (columns * rows) to ensure valid mine placement
     */
    Board(int columns, int rows, int mines);

    // * Getters

    /**
     * @brief Gets the number of columns in the board
     * @return int Number of columns
     */
    int getColumns() const;

    /**
     * @brief Gets the number of rows in the board
     * @return int Number of rows
     */
    int getRows() const;

    /**
     * @brief Gets a read-only copy of the cell at specified coordinates
     * @param column Column index (0-based)
     * @param row Row index (0-based)
     * @return Cell Copy of the cell at the specified position
     * @pre isValidBoardCoordinate(column, row)
     */
    Cell getCell(int column, int row) const;

    /**
     * @brief Gets a mutable reference to the cell at specified coordinates
     * @param column Column index (0-based)
     * @param row Row index (0-based)
     * @return Cell& Reference to the cell at the specified position
     * @pre isValidBoardCoordinate(column, row)
     */
    Cell &getCell(int column, int row);

    /**
     * @brief Gets the content type of the cell at specified coordinates
     * @param column Column index (0-based)
     * @param row Row index (0-based)
     * @return CellContent The content type of the cell
     * @pre isValidBoardCoordinate(column, row)
     */
    CellContent getCellContent(int column, int row) const;

    /**
     * @brief Gets a copy of the entire board structure
     * @return std::vector<std::vector<Cell>> 2D vector containing all board cells
     */
    std::vector<std::vector<Cell>> getBoard() const;

    /**
     * @brief Gets the total number of mines on the board
     * @return int Number of mines
     */
    int getMines() const;

    // * Setters

    /**
     * @brief Sets the content of a specific cell
     * @param column Column index (0-based)
     * @param row Row index (0-based)
     * @param content The new content type for the cell
     * @pre isValidBoardCoordinate(column, row)
     */
    void setCellContent(int column, int row, CellContent content);

    /**
     * @brief Randomly places mines across the board
     *
     * Distributes the specified number of mines randomly across the board,
     * ensuring no cell contains more than one mine.
     */
    void setMines();

    /**
     * @brief Calculates and sets numbers for all non-mine cells
     *
     * For each cell that doesn't contain a mine, calculates the number
     * of adjacent mines and sets the cell's content and nearby mine count.
     */
    void setNumber();

    // * Utils

    /**
     * @brief Calculates the number of mines adjacent to a specific cell
     * @param column Column index (0-based)
     * @param row Row index (0-based)
     * @return int Number of mines in the 8 adjacent cells (0-8)
     * @pre isValidBoardCoordinate(column, row)
     */
    int calculateNearbyMines(int column, int row);

    /**
     * @brief Validates if the given coordinates are within board bounds
     * @param column Column index to validate
     * @param row Row index to validate
     * @return bool True if coordinates are valid, false otherwise
     */
    bool isValidBoardCoordinate(int column, int row) const;

    /**
     * @brief Renders the board to the terminal with borders and labels
     *
     * Displays the current state of the board with:
     * - Column labels (A, B, C, ...)
     * - Row labels (1, 2, 3, ...)
     * - Bordered grid showing cell states
     * - Colored numbers for mine counts
     */
    void print() const;

    /**
     * @brief Generates random valid coordinates within the board
     * @return std::array<int, 2> Array containing [column, row] coordinates
     * @note Uses std::random_device for true randomness!
     */
    std::array<int, 2> generateRandomCoordinates() const;
};

#endif // BOARD_H